#include "Send.h"

Send::Send()
{
	frameCnt = 0;														// T�ller hvilket frame send-metoden er n�et til.
	timerLength = 3;													// Hvor l�nge der m� g� fra et frame sendes til der modtages et Ack.
	maxAttempts = 5;													// Hvor mange gange et frame m� gensendes inden der opgives.
	addrs = Addresses::getInstance();									// En pointer til Addresses-klassen oprettes.
	buff = Buffer::getInstance();										// En pointer til Buffer-klassen oprettes.
}

Send::~Send()
{}

void Send::sendFrames(vector<string> vec, string addr)
{
	frameVector = vec;
	otherAddress = addr.substr(0, 4);									// Adressen p� den anden enhed
	thisAddress = addr.substr(4, 4);									// Adressen p� denne enhed
	addrs->setThisAddress(thisAddress);									// Denne enheds adresse modtaget fra App-laget gemmes p� enheden.
	
	if (otherAddress != "1111")											// Hvis modtageradressen er broadcastadressen skal denne ikke gemmes p� enheden.
	{
		addrs->setOtherAddress(otherAddress);							// Modtageradressen gemmes p� enheden.
	}
	string thisFrame;
	int failedAttempts = 0;												// En counter nulstilles i starten af en transmission, og t�lles op hver gang der ikke modtages et Ack for et frame.

	while (frameCnt < frameVector.size())
	{
		thisFrame = frameVector[frameCnt];								// Frames i vektoren sendes hver for sig.	
		frameToBuffer(thisFrame);										// Bitset'ene s�ttes ind i bufferen, s� det fysiske lag kan hente og sende dem.
		addrs->setAck(0);												// Et nyt frame er sendt, og ack s�ttes lig 0.
		addrs->setFrameNo(frameCnt);
		int ackCountdown = timerLength;									// ackCountdown fungerer som en timer p� et antal sekunder.

		while (true && !buff->checkFlag(0))
		{
			this_thread::sleep_for(chrono::seconds(1));					// Hvert sekund tjekkes det om et ACK er modtaget.

			if (addrs->getAck() == 1)
			{
				failedAttempts = 0;										// Hvis det er tilf�ldet nulstilles failedAttempts og loopet afbrydes.
				cout << "Frame " << frameCnt << " successful				" << thisFrame << endl;
				frameCnt++;
				break;
			}
			cout << "No ack received" << endl;
			ackCountdown--;												// Hvis ikke t�lles timeren ned.

			if (ackCountdown == 0)										// Hvis timeren er udl�bet t�lles failedAttempts op.
			{
				failedAttempts++;
				ackCountdown = timerLength;
				cout << "Failed attempts = " << failedAttempts << endl;

				if (failedAttempts == maxAttempts)						// Hvis failedAttemps rammer gr�nsen afbrydes transmissionen.
				{
					cout << "Transmission failed" << endl;
					return;
				}
				frameToBuffer(thisFrame);								// Framet gensendes
			}
		}	
	}
	cout << "Transmission complete" << endl;
}

void Send::frameToBuffer(string thisFrame)
{
	for (int i = 0; i < thisFrame.length(); i++)
	{
		bitset<4> MSBs(bitset<8>(thisFrame[i]).to_string().substr(0, 4));
		bitset<4> LSBs(bitset<8>(thisFrame[i]).to_string().substr(4, 4));

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