#include "InframeArchive.h"

InframeArchive::InframeArchive()
{}

InframeArchive::InframeArchive(string astr)								// En instans af klassen oprettes med filen der skal sendes som parameter på string-form af ascii-karakterer. 
{
	asciiString = astr;
	frameType = 0;														// Altid I-frames
	dataBitSize = 16;													// Max størrelse på datadelen i et frame [bytes]
	receiverAndSender = asciiString.substr(0, 8);						// Kopierer de første 8 bit i datasektionen fra App-laget, da denne indeholder adresserne der benyttes til at sende denne besked.
}

void InframeArchive::sendFrames()										// Denne metode kaldes af tråden der tjekker bufferen fra App-laget, når der er noget der skal sendes.
{																		// Den gennemgår metoderne og sender frameVectoren videre til Send-klassen.
	makeFrames();
	Send s;
	s.sendFrames(frameVector, receiverAndSender);
}

void InframeArchive::makeFrames()										//Alt dataet deles op i mindre sektioner, der hver især skal frames.
{
	string substring;
	char last = '0';
	int frameNo = 0;
	for (int i = 0; i < asciiString.length(); i += dataBitSize)			
	{
		if (i >= asciiString.length() - dataBitSize)					// Hvis framet er det sidste i beskeden sættes char'en "last" til 1.
		{
			last = '1';
		}
		substring = asciiString.substr(i, dataBitSize);
		Inframe f(substring, frameType, frameNo, last, receiverAndSender);
		f.runInframe();
		frameVector.push_back(f.getFinalFrame());						// De færdige frames gemmes i frameVector.
		frameNo++;
	}
}

void InframeArchive::printVector()										// Metode brugt til debugging.
{
	for (int i = 0; i < frameVector.size(); i++)
	{
		cout << frameVector[i] << endl;
	}
}

InframeArchive::~InframeArchive()
{}
