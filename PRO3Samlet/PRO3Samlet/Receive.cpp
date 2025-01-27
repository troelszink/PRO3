#include "Receive.h"

Receive::Receive()
{
	frameCnt = 0;														// T�ller hvilket frame send-metoden er n�et til.
	bitstream = "";														// Bruges i receiveBits til midlertidigt at gemme de modtagne nibbles.
	minFrameLength = 40;												// S�rger for at der ikke tjekkes efter flag inden det er realistisk at et frame er modtaget.
	addrs = Addresses::getInstance();									// En pointer til Addresses-klassen oprettes.
	buff = Buffer::getInstance();										// En pointer til Buffer-klassen oprettes.
}

Receive::~Receive()
{}

void Receive::receiveBits(bitset<4> bits)
{									
	bitstream += bits.to_string();										// Den modtagne bitset overs�ttes til en string, og tilf�jes til bitstream.

	if (bitstream.length() >= minFrameLength)							// N�r bitstream-l�ngden overstiger minimum tjekkes det om der er modtaget �t flag.
	{
		int pos1 = bitstream.find("01111110");

		if (pos1 != string::npos)										// Findes der et flag, tjekkes der efter endnu et flag efter det allerede fundne.
		{
			int pos2 = bitstream.find("01111110", pos1 + 8);

			if (pos2 != string::npos)									// Findes begge flag gemmes bitstrengen som et frame fra flag til flag, og de foreg�ende 0'er slettes.
			{
				receivedFrame = bitstream.substr(pos1, pos2 - pos1 + 8);
				bitstream.erase(0, pos2 + 8);

				interpret(receivedFrame);								// Det modtagne frame analyseres.
			}
		}
	}
}

void Receive::interpret(string recFrm)
{
	Deframe df(recFrm, thisAddress, otherAddress);						// Det modtagne frame sendes til deframing, hvor de forskellige dele tilf�jet i Inframe pilles og unders�ges.
	df.runDeframe();

	if (df.getReceiveSuccess() == false)								// Hvis der blev opdaget fejl i CRC8 eller adresser g�res der intet.
	{
		cout << "ReceiveSuccess == false" << endl;
		return;
	}																	// Hvis ikke, tjekkes typen af frame.
	else if (df.getFrameType() == 'I' && df.getFrameNo() == frameCnt)	// Hvis det er I-frame og forventede framenummer
	{
		asciiFile += df.getAsciiDataBit();								// Data fra framen tilf�jes den endelige fil
		frameCnt = (frameCnt + 1) % 8;
		string ackAddresses = df.getOtherAddress() + df.getThisAddress();

		//*********************Send Ack:***********************			// N�r frametdataet er tilf�jet til asciiFile skal der sendes et Ack.
		sendAck(df.getLastFrame(), ackAddresses);

		if (df.getLastFrame() == '1')
		{
			while (true && !buff->checkFlag(0))
			{
				try
				{
					buff->addTo_datalinkToApp(asciiFile);				// N�r det sidste frame er modtaget gemmes filen i bufferen til App-laget.
				}
				catch (...)
				{
					this_thread::sleep_for(chrono::milliseconds(10));
				}
			}
			asciiFile = "";												// asciiFile og frameCnt nulstilles til n�ste fil
			frameCnt = 0;												
		}
	}
	else if (df.getFrameType() == 'S')									// Hvis det modtagne frame er et Ack opdateres frameCnt til d�t der angives i Ack'et.
	{
		int nextFrame = (addrs->getFrameNo() + 1) % 8;
		if (df.getFrameNo() == nextFrame)
		{
			if (df.getLastFrame())
			{
				cout << "Transmission Successfull" << endl;				// Hvis Acket er for det sidste frame er der sket en succesfuld transmission.
			}
			addrs->setAck(1);											// ack s�ttes til 1 for at sige at et frame er modtaget korrekt, og at det n�ste frame godt kan afsendes.
		}																								
	}
}

void Receive::sendAck(char lastframe, string ackaddrs)
{
	Inframe ackFrame("", 1, frameCnt, lastframe, ackaddrs);				// Inframe-klassen kaldes med en tom data-sektion, frametype = 1, frameCnt p� det n�ste frame der �nskes modtaget, hvorvidt der kvitteres for det sidste frame, og adresserne.
																		// Framet overs�ttes til bitset-nibbles og inds�ttes i bufferen til det fysiske lag.
	for (int i = 0; i < ackFrame.getFinalFrame().length(); i++)
	{
		bitset<4> MSBs(bitset<8>(ackFrame.getFinalFrame()[i]).to_string().substr(0, 4));
		bitset<4> LSBs(bitset<8>(ackFrame.getFinalFrame()[i]).to_string().substr(4, 4));

		while (true && !buff->checkFlag(0))
		{
			try
			{
				buff->addTo_datalinkToSound(MSBs);
				break;
			}
			catch (...)
			{
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
		while (true && !buff->checkFlag(0))
		{
			try
			{
				buff->addTo_datalinkToSound(LSBs);
				break;
			}
			catch (...)
			{
				this_thread::sleep_for(chrono::milliseconds(10));
			}
		}
	}
	buff->setFlag(1, true);
	buff->setFlag(3, true);
}
