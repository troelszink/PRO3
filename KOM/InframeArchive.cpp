#include "InframeArchive.h"

InframeArchive::InframeArchive()
{}

InframeArchive::InframeArchive(string astr)				//En instans af klassen oprettes med filen, der skal sendes, som parameter på string-form af ascii-karakterer. 
{
	asciiString = astr;
	frameType = 0;
	dataBitSize = 16;
}

void InframeArchive::sendFrames()						//Denne metode kaldes af tråden der tjekker bufferen fra App-laget, når der er noget der skal sendes.
{														//Den gennemgår metoderne og sender frameVectoren videre til Transmission-klassen.
	extractAddresses();
	splitAsciiString();
	makeFrames();

	Send s;
	s.sendFrames(frameVector, receiverAndSender);
}

void InframeArchive::extractAddresses()					//Kopierer de første 8 bit i datasektionen fra App-laget, da denne indeholder adresserne der benyttes til at sende denne besked.
{
	receiverAndSender = asciiString.substr(0, 8);
}

void InframeArchive::splitAsciiString()					//Alt dataet deles op i mindre sektioner der hver især skal frames. Disse sektioner gemmes i en vektor.
{
	string substring;
	for (int i = 0; i < asciiString.length(); i = i + dataBitSize)
	{
		substring = asciiString.substr(i, dataBitSize);
		dataBitVector.push_back(substring);
	}
}

void InframeArchive::makeFrames()						//dataBitVektoren gennemgås og frames hver for sig og gemmes i frameVector.
{
	char last = '0';
	for (int i = 0; i < dataBitVector.size(); i++)
	{
		if (i == dataBitVector.size() - 1)				//Hvis framet er det sidste i beskeden sættes char'en "last" til 1.
		{
			last = '1';
		}
		string d = dataBitVector[i];
		Inframe f(d, frameType, i, last, receiverAndSender);
		f.runInframe();
		string m = f.getFinalFrame();
		frameVector.push_back(m);						//De færdige frames gemmes i frameVector.
	}
}

void InframeArchive::printVector()						//Metode brugt til debugging.
{
	for (int i = 0; i < frameVector.size(); i++)
	{
		cout << frameVector[i] << endl;
	}
}

InframeArchive::~InframeArchive()
{}
