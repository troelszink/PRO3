#include "Send.h"

Send::Send()
{
	frameCnt = 0;														// Tæller hvilket frame send-metoden er nået til.
	timerLength = 3;													// Hvor længe der må gå fra et frame sendes til der modtages et Ack.
	maxAttempts = 5;													// Hvor mange gange et frame må gensendes inden der opgives.
	addrs = Addresses::getInstance();									// En pointer til Addresses-klassen oprettes.
	buff = Buffer::getInstance();										// En pointer til Buffer-klassen oprettes.
}

Send::~Send()
{}

void Send::sendFrames(vector<string> vec, string addr)
{
	frameVector = vec;
	otherAddress = addr.substr(0, 4);									// Adressen på den anden enhed
	thisAddress = addr.substr(4, 4);									// Adressen på denne enhed
	
	addrs->setThisAddress(thisAddress);									// Denne enheds adresse modtaget fra App-laget gemmes på enheden.
	if (otherAddress != "1111")											// Hvis modtageradressen er broadcastadressen skal denne ikke gemmes på enheden.
	{
		addrs->setOtherAddress(otherAddress);							// Modtageradressen gemmes på enheden.
	}

	string thisFrame;
	int failedAttempts = 0;												// En counter nulstilles i starten af en transmission, og tælles op hver gang der ikke modtages et Ack for et frame.

	while (frameCnt < frameVector.size())
	{
		thisFrame = frameVector[frameCnt];								// Frames i vektoren sendes hver for sig.	
		frameToBuffer(thisFrame);										// Bitset'ene sættes ind i bufferen, så det fysiske lag kan hente og sende dem.
		addrs->setAck(0);												// Et nyt frame er sendt, og ack sættes lig 0.
		int ackCountdown = timerLength;									//ackCountdown fungerer som en timer på et antal sekunder.

		while (true)
		{
			this_thread::sleep_for(chrono::seconds(60));					// Hvert sekund tjekkes det om et ACK er modtaget.
			if (addrs->getAck() == 1)
			{
				failedAttempts = 0;										// Hvis det er tilfældet nulstilles failedAttempts og loopet afbrydes.
				ackCountdown = timerLength;
				break;
			}
			//cout << "Sender:	No ack received" << endl;
			ackCountdown--;												// Hvis ikke tælles timeren ned.

			if (ackCountdown == 0)										// Hvis timeren er udløbet tælles failedAttempts op.
			{
				frameToBuffer(thisFrame);
				failedAttempts++;
				ackCountdown = timerLength;
				//cout << "Sender:	Failed attempts = " << failedAttempts << endl;

				if (failedAttempts == maxAttempts)						// Hvis failedAttemps rammer grænsen afbrydes transmissionen.
				{
					//cout << "Sender:	Transmission failed" << endl;
					return;
				}
			}
		}
		frameCnt++;
		cout << "Frame " << frameCnt << " successful				" << thisFrame << endl;
	}
	cout << "Transmission complete" << endl;
}

void Send::frameToBuffer(string thisFrame)
{
	cout << thisFrame << endl;
	for (int i = 0; i < thisFrame.length(); i++)
	{
		bitset<4> MSBs(bitset<8>(thisFrame[i]).to_string().substr(0, 4));
		bitset<4> LSBs(bitset<8>(thisFrame[i]).to_string().substr(4, 4));

		buff->addTo_datalinkToSound(MSBs);
		buff->addTo_datalinkToSound(LSBs);
	}
	Buffer::getInstance()->setFlag(1, true);
	Buffer::getInstance()->setFlag(3, true);
	///////////////////////////// Sæt flag til DSP om at et frame er sendt til buffer ///////////////////////
}
