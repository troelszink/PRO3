#include "Inframe.h"

Inframe::Inframe()
{}

Inframe::Inframe(string adb, int type, int fno, char last, string addrs)		 
{																			// Hver sektion af filen gennemgår denne klasse, der tilføjer adresser, kontrol, fejltjek mm.
	asciiDataBit = adb;														// Sektion af fil.
	frameType = type;														// Typen af frame, enten I-frame med data der skal sendes, eller S-frame med Acknowledges
	frameNo = fno;															// Sektionsnummer
	lastFrame = last;														// Sættes til 1 hvis denne sektion er den sidste i beskeden, ellers 0.
	addresses = addrs;														// Sender- og modtageradresser for beskeden.
	flag = "01111110";														// Flag der definerer start og slut på framet. 
}

void Inframe::runInframe()
{
	expandToBinary();
	addControl();
	addAddresses();
	encodeCRC8();
	bitstuffing();
	addFlag();
	addExtraZeroes();
	compressToAscii();
}

void Inframe::expandToBinary()
{
	for (int i = 0; i < asciiDataBit.length(); i++)
	{
		bitset<8> tobit(asciiDataBit[i]);
		dataBit += tobit.to_string();
	}
}

void Inframe::addControl()
{
	string control;
	if (frameType == 0)
		control = "0000";
	else if (frameType == 1)
		control = "1000";

	int smallFrameNo = frameNo % 8;
	control += lastFrame + bitset<3>(smallFrameNo).to_string();
	frame = control + dataBit;
}

void Inframe::addAddresses()													// Adresser tilføjes
{
	frame = addresses + frame;
}

void Inframe::encodeCRC8()														// Der foretages CRC-8 som fejltjek.
{
	string frameCopy = frame + "00000000";										// En kopi af framet oprettes, og der lægges 8 0-bit til sidst.
	string divisor = "100000111";												// Der vælges en standard divisor på 9 bits.

	for (int i = 0; frameCopy.substr(0, frameCopy.length() - 8).find_first_of("1") != string::npos; i++)		
	{																			// Så længe dataword indeholder andet end 0'er, kør statements
		if (frameCopy[i] != '0')												// Et for-loop gennemgår framet, og stopper først når alle bits i frameCopy, foruden de sidste 8, er 0.
		{																		// Hvis det aktuelle bit er 1 så fortages divisionen. Hvis ikke fortsætter loopet til næste bit. 
			string s = frameCopy.substr(i, 9);									// Der tages 9 bit ud fra den aktuelle position og frem efter.
			string result = "000000000";
			for (int n = 0; n < 9; n++)
			{
				result[n] = ((s[n] - '0') ^ (divisor[n] - '0')) + '0';			// Substringen gennemgås og der XOR'es med divisoren for hver position.
			}
			frameCopy.replace(i, 9, result);									// Resultatet heraf indsættes dér hvor substring blev taget ud. 
		}																		// Dette gøres så længe der andet en 0'ere i framet, foruden remainderen.
	}							
	string remainder = frameCopy.substr(frameCopy.length() - 8, 8);				// De sidste 8 bit tages ud og tilføjes bag ved framet. 
	frame += remainder;
}

void Inframe::bitstuffing()														// For at undgå at der opstår flag midt i framet indsættes der 0'ere midt i eventuelle flag. 
{
	int i = 0;
	while (i < frame.length())													// Et indeks sættes til at gennemgå framet.
	{
		if (frame.find("011111", i) != string::npos)							// Hvis der findes en substring på 011111 indsættes et 0 efter. 
		{																		// På den måde kan der aldrig opstå et 0 efterfulgt af 6 1'ere, hvilket svare til flaget.
			int pos = frame.find("011111", i);									// Findes der et "flag" ordnes det og indekset sættes efter det fundne flag og der tjekkes efter flere.
			frame.insert(pos + 6, "0");
			i = pos + 1;
		}
		else																	// Findes der ingen flag afbrydes while-loopet.
		{
			break;
		}
	}
}

void Inframe::addFlag()															// Flag tilføjes før og efter framet.
{
	frame = flag + frame + flag;
}

void Inframe::addExtraZeroes()													// Da stringen af binære værdier skal laves tilbage til ascii-karakterer skal længden gå op i 8.
{
	if (frame.length() % 8 != 0)												// Der indsættes derfor et passende antal 0'er efter det sidste flag.
	{
		int extraZeroes = 8 - (frame.length() % 8);

		for (int i = 0; i < extraZeroes; i++)
		{
			frame += "0";
		}
	}
}

void Inframe::compressToAscii()
{
	stringstream sstream(frame);												// Framet indsættes i en stringstream.
	char c;
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;														// Så længe enden af sstream ikke er nået, tages 8 bit ud af sstream.

		c = char(bits.to_ulong());												// Disse 8 bit oversættes til en char, som tilføjes til en ny string kaldet finalFrame.
		finalFrame += c;
	}
	finalFrame.erase(finalFrame.length() - 1, 1);								// Den sidste char i finalFrame fjernes, da denne ikke kommer fra framet.
}

string Inframe::getFinalFrame()
{
	return finalFrame;
}

string Inframe::getDataBit()													//Debugging
{
	return dataBit;
}

Inframe::~Inframe()
{}
