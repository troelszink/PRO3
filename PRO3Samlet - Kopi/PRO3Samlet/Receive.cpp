#include "Receive.h"

Receive::Receive()
{
	frameCnt = 0;														// Tæller hvilket frame send-metoden er nået til.
	bitstream = "";														// Bruges i receiveBits til midlertidigt at gemme de modtagne nibbles.
	minFrameLength = 40;												// Sørger for at der ikke tjekkes efter flag inden det er realistisk at et frame er modtaget.
	buff = Buffer::getInstance();
}

Receive::~Receive()
{}

void Receive::receiveBits(bitset<4> bits)
{
	string nibble = bits.to_string();									// Den modtagne bitset oversættes til en string, og tilføjes til bitstream.
	bitstream += nibble;

	if (bitstream.length() >= minFrameLength)							// Når bitstream-længden overstiger minimum tjekkes det om der er modtaget ét flag.
	{
		int pos1 = bitstream.find("01111110");

		if (pos1 != string::npos)										// Findes der et flag, tjekkes der efter endnu et flag efter det allerede fundne.
		{
			int pos2 = bitstream.find("01111110", pos1 + 8);

			if (pos2 != string::npos)									// Findes begge flag gemmes bitstrengen som et frame fra flag til flag, og de foregående 0'er slettes.
			{
				receivedFrame = bitstream.substr(pos1, pos2 - pos1 + 8);
				bitstream.erase(0, pos2 + 8);

				try
				{
					interpret(receivedFrame);								// Det modtagne frame analyseres.
				}
				catch (...)
				{

				}
			}
		}
	}
}

void Receive::interpret(string recFrm)
{
	Deframe df(recFrm, thisAddress, otherAddress);						// Det modtagne frame sendes til deframing, hvor de forskellige dele tilføjet i Inframe pilles og undersøges.
	df.runDeframe();

	if (df.getReceiveSuccess() == false)								// Hvis der blev opdaget fejl i CRC8 eller adresser gøres der intet.
	{
		cout << "ReceiveSuccess == false" << endl;
		return;
	}
	else																// Hvis ikke, tjekkes typen af frame.
	{
		if (df.getFrameType() == 'I')
		{
			if (df.getFrameNo() == frameCnt)							// Hvis det er et I-frame og nummeret matcher frameCnt, tilføjes dataet til en string der i sidste ende skal indeholde hele den sendte fil.
			{
				asciiFile += df.getAsciiDataBit();

				if (df.getLastFrame() == true)
				{
					while (true && !buff->checkFlag(0))
					{
						try
						{
							buff->addTo_datalinkToApp(asciiFile);				// Når det sidste frame er modtaget gemmes filen i bufferen til App-laget.	
						}
						catch (...)
						{
							this_thread::sleep_for(chrono::milliseconds(20));
						}
					}
				}

				if (buff->checkFlag(0))
					throw "Exit";
				//********************************Send Ack:********************************************************************
				cout << "Enter ACK" << endl;
				frameCnt = (df.getFrameNo() + 1) % 8;					// Når frametdataet er tilføjet til asciiFile skal der sendes et Ack.		
				char lastF;
				if (df.getLastFrame())
				{
					lastF = '1';
				}
				else
				{
					lastF = '0';
				}

				string ackAddresses = df.getOtherAddress() + df.getThisAddress();
				Inframe ackFrame("", 1, frameCnt, lastF, ackAddresses);		// Inframe-klassen kaldes med en tom data-sektion, frametype = 1, frameCnt på det næste frame der ønskes modtaget, hvorvidt der kvitteres for det sidste frame, og adresserne.
																			// Framet oversættes til bitset-nibbles og indsættes i bufferen til det fysiske lag.
				for (int i = 0; i < ackFrame.getFinalFrame().length(); i++)
				{
					bitset<4> MSBs(bitset<8>(ackFrame.getFinalFrame()[i]).to_string().substr(0, 4));
					bitset<4> LSBs(bitset<8>(ackFrame.getFinalFrame()[i]).to_string().substr(4, 4));

					buff->addTo_datalinkToSound(MSBs);
					buff->addTo_datalinkToSound(LSBs);
				}
				
				buff->setFlag(1, true);
				buff->setFlag(3, true);
			}
		}
		else if (df.getFrameType() == 'S')									// Hvis det modtagne frame er et Ack opdateres frameCnt til dét der angives i Ack'et.
		{
			//frameCnt = df.getFrameNo();
			int nextFrame = (addrs->getFrameNr() + 1) % 8;
			if (df.getFrameNo() == nextFrame)
			{
				if (df.getLastFrame())
				{
					cout << "Transmission Successfull" << endl;				// Hvis Acket er for det sidste frame er der sket en succesfuld transmission.
				}
				addrs->setAck(1);											// ack sættes til 1 for at sige at et frame er modtaget korrekt, og at det næste frame godt kan afsendes.
			}
																										
		}
	}
}