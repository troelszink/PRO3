#include "Inframe.h"

Inframe::Inframe()
{}

Inframe::Inframe(string dtbA, int type, int fno, char last, string addr)	// Hver sektion af filen gennemg�r denne klasse, der tilf�jer adresser, kontrol, fejltjek mm. 
{
	asciiDataBit = dtbA;			// Sektion af fil.
	frameType = type;				// Typen af frame, enten I-frame med data der skal sendes, eller S-frame med Acknowledges
	frameNo = fno;					// Sektionsnummer
	lastFrame = last;				// S�ttes til 1 hvis denne sektion er den sidste i beskeden, ellers 0.
	addresses = addr;				// Sender- og modtageradresser for beskeden.
	flag = "01111110";				// Flag der definerer start og slut p� framet. 
}

void Inframe::runInframe()
{
	expandToBinary();

	if (frameType == 0)
		addIControl();
	else if (frameType == 1)
		addSControl();

	addAddresses();
	encodeCRC8();
	bitstuffing();
	addFlag();
	addExtraZeroes();
	compressToAscii();
}

void Inframe::expandToBinary()													// For at kunne tilf�je fejltjek osv. omskrives sektionen fra ascii-karakterer til en string af bin�r-v�rdier.
{
	int asciiLength = asciiDataBit.length();									// asciiLength s�ttes lig sektionens l�ngde, dvs. dens m�ngde af ascii-karakterer.
	string binaryString = "";													// En tom string, binaryString, oprettes hvor de l�bende konverterede ascii v�rdier gemmes i.

	for (int i = 1; i <= asciiLength; i++)										// For loopet vil forts�tte indtil hele stringen asciiDataBit er l�bet igennem.
	{
		int valueAscii = int(asciiDataBit[asciiLength - i]);					// Decimalv�rdien af den nuv�rende ASCII karekter gemmes som en int kaldet valueAscii. Den sidste char i binaryString gemmes f�rst, grundet konverteringsmetoden fra ASCII til bin�r (omvendt repr�sentation)
		int valueCopy = valueAscii;												// En kopi af valueAscii gemmes i heltallet: valueCopy. 

		if (valueCopy == -26)
		{
			binaryString += "01100111";	// Omvendt "�"
			goto nextIndex;
		}
		else if (valueCopy == -58)
		{
			binaryString += "01100011"; // Omvendt "�"
			goto nextIndex;
		}
		else if (valueCopy == -8)
		{
			binaryString += "00011111"; // Omvendt "�"
			goto nextIndex;
		}
		else if (valueCopy == -40)
		{
			binaryString += "00011011"; // Omvendt "�"
			goto nextIndex;
		}
		else if (valueCopy == -27)
		{
			binaryString += "10100111"; // Omvendt "�"
			goto nextIndex;
		}
		else if (valueCopy == -59)
		{
			binaryString += "10100011"; // Omvendt "�"
			goto nextIndex;
		}
		else
		{
			while (valueAscii > 0)													// While-loopet forts�tter imens v�rdien af valueAscii er over 0.
			{
				if (valueAscii % 2 != 0)											// Modulus 2 tages af valueAscii. Hvis der er rest tilf�jes et "1" til binaryString
				{
					binaryString.push_back('1');
				}
				else
				{																	// Ellers hvis resten er 0, tilf�jes et "0" til stringen binary.
					binaryString.push_back('0');
				}
				valueAscii /= 2;													// valueAscii s�ttes lig dens halve v�rdi. Dette vil svarer til at shifte den bin�re v�rdi en til h�jre.
			}
			// Da while-loopet ikke tager h�jde for at en ASCII-karakter er 8 bits lang, skal der tjekkes om der mangler 0'er til venstre for det mest betydende bit p� 1
			// for at repr�sentere den korrekte ASCII-karakter.
			if (valueCopy < 128 && valueCopy > 63)
			{
				binaryString.append("0");
			}
			if (valueCopy < 64 && valueCopy>31)
			{
				binaryString.append("00");
			}
			if (valueCopy < 32 && valueCopy > 15)
			{
				binaryString.append("000");
			}
			if (valueCopy < 16 && valueCopy > 7)
			{
				binaryString.append("0000");
			}
			if (valueCopy < 8 && valueCopy > 3)
			{
				binaryString.append("00000");
			}
			if (valueCopy < 4 && valueCopy > 1)
			{
				binaryString.append("000000");
			}
			if (valueCopy < 2 && valueCopy > 0)
			{
				binaryString.append("0000000");
			}
		}
	nextIndex:;
	}
	reverse(binaryString.begin(), binaryString.end());							// Pga. m�den elementer tilf�jes til binaryString, vil de v�re i omvendt r�kkef�lge. Den skal derfor vendes.
	dataBit = binaryString;														// dataBit s�ttes lig binaryString.
}

void Inframe::addIControl()														// Hvis Inframe blev kaldt fra InframeArchive vil frameType = 0, og der er tale om data der skal sendes, alts� et I-frame.
{																				// I-framet er bygget op s�ledes:
	string controlStr = "00000000";												// | Type (1 bit) | Sekvensnr. (3 bit) | LastFrame (1 bit) | Reserveret (3 bit) | 
	int smallFrameNo = frameNo % 8;												// Der tages modulus 8 til sektionsnummeret, for at f� en v�rdi fra 0-7, s� det kan repr�senteres p� 3 bit.
	controlStr.replace(1, 3, bitset<3>(smallFrameNo).to_string());
	controlStr[4] = lastFrame;													// lastFrame inds�ttes p� position 4.
	frame = controlStr + dataBit;												// De 8 controlbit l�gges foran dataBit i en ny string kaldet frame.
}

void Inframe::addSControl()														// Hvis Inframe blev kaldt fra Transmission betyder det at der er tale om et S-frame og frametype = 1.
{																				// S-framet er bygget op s�ledes:
	string controlStr = "10000000";												// | Type (2 bit) | Kode (2 bit) | LastFrame (1 bit) | N�ste Framenr. (3 bit) | 
	controlStr[4] = lastFrame;
	if (lastFrame == '0')														// Hvis dette er et Ack p� det sidste frame i en besked s�ttes framenr. blot til 0, og controlbittene tilf�jes framet.
	{
		controlStr.replace(5, 3, bitset<3>(frameNo).to_string());
	}
	frame = controlStr + dataBit;
}

void Inframe::addAddresses()													// Adresser tilf�jes
{
	frame = addresses + frame;
}

void Inframe::encodeCRC8()														// Der foretages CRC-8 som fejltjek.
{
	string frameCopy = frame + "00000000";										// En kopi af framet oprettes, og der l�gges 8 0-bit til sidst.
	string divisor = "100000111";												// Der v�lges en standard divisor p� 9 bits.

	for (int i = 0; frameCopy.substr(0, frameCopy.length() - 8).find_first_of("1") != string::npos; i++)		//S� l�nge dataword indeholder andet end 0'ere, k�r statements
	{
		if (frameCopy[i] != '0')												// Et for-loop gennemg�r framet, og stopper f�rst n�r alle bits i frameCopy, foruden de sidste 8, er 0.
		{																		// Hvis det aktuelle bit er 1 s� fortages divisionen. Hvis ikke forts�tter loopet til n�ste bit. 
			string s = frameCopy.substr(i, 9);									// Der tages 9 bit ud fra den aktuelle position og frem efter.
			string result = "000000000";
			for (int n = 0; n < 9; n++)
			{
				result[n] = ((s[n] - '0') ^ (divisor[n] - '0')) + '0';			// Substringen gennemg�s og der XOR'es med divisoren for hver position.
			}
			frameCopy.replace(i, 9, result);									// Resultatet heraf inds�ttes d�r hvor substring blev taget ud. 
		}																		// Dette g�res s� l�nge der andet en 0'ere i framet, foruden remainderen.
	}							
	string remainder = frameCopy.substr(frameCopy.length() - 8, 8);				// De sidste 8 bit tages ud og tilf�jes bag ved framet. 
	frame = frame + remainder;
}

void Inframe::bitstuffing()														// For at undg� at der opst�r flag midt i framet inds�ttes der 0'ere midt i eventuelle flag. 
{
	int i = 0;
	while (i < frame.length())													// Et indeks s�ttes til at gennemg� framet.
	{
		if (frame.find("011111", i) != string::npos)							// Hvis der findes en substring p� 011111 inds�ttes et 0 efter. 
		{																		// P� den m�de kan der aldrig opst� et 0 efterfulgt af 6 1'ere, hvilket svare til flaget.
			int pos = frame.find("011111", i);									// Findes der et "flag" ordnes det og indekset s�ttes efter det fundne flag og der tjekkes efter flere.
			frame.insert(pos + 6, "0");
			i = pos + 1;
		}
		else																	// Findes der ingen flag afbrydes while-loopet.
		{
			break;
		}
	}
}

void Inframe::addFlag()															// Flag tilf�jes f�r og efter framet.
{
	frame = flag + frame + flag;
}

void Inframe::addExtraZeroes()													// Da stringen af bin�re v�rdier skal laves tilbage til ascii-karakterer skal l�ngden g� op i 8.
{
	if (frame.length() % 8 != 0)												// Der inds�ttes derfor et passende antal 0'ere efter det sidste flag.
	{
		int extraZeroes = 8 - (frame.length() % 8);

		for (int i = 0; i < extraZeroes; i++)
		{
			frame = frame + "0";
		}
	}
}

void Inframe::compressToAscii()
{
	stringstream sstream(frame);												// Framet inds�ttes i en stringstream.
	char c;
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;														// S� l�nge enden af sstream ikke er n�et, tages 8 bit ud af sstream.

		c = char(bits.to_ulong());												// Disse 8 bit overs�ttes til en char, som tilf�jes til en ny string kaldet finalFrame.
		finalFrame += c;
	}
	finalFrame.erase(finalFrame.length() - 1, 1);								// Den sidste char i finalFrame fjernes, da denne ikke kommer fra framet.
}

string Inframe::getFinalFrame()
{
	return finalFrame;
}

string Inframe::getDataBit()
{
	return dataBit;
}

Inframe::~Inframe()
{
}
