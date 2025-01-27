#include "Deframe.h"

Deframe::Deframe()
{}

Deframe::Deframe(string frm, string taddr, string oaddr)		// Denne klasse bruges til at at afkode en modtagen bitstring.
{
	bitString = frm;
	thisAddress = taddr;
	otherAddress = oaddr;
}

void Deframe::runDeframe()
{
	deflag();
	bitdestuffing();
	decodeCRC8();
}

void Deframe::deflag()											// Fjerner de to flag forrest og bagerst.
{
	bitString.erase(0, 8);
	bitString.erase(bitString.length() - 8, 8);
}

void Deframe::bitdestuffing()									// Fjerner de ekstra 0'er der inds�ttes i tilf�lde af utilsigtet flag.
{
	int i = 0;
	while (i < bitString.length())
	{
		if (bitString.find("111110", i) != string::npos)		// bitstring tjekkes igennem efter bitstuffing-sekvensen, og fjerner de ekstra 0 der blev tilf�jet.
		{
			int pos = bitString.find("111110", i);
			bitString.erase(pos + 5, 1);
			i = pos + 5;										// Indekset placeres efter sekvensen og der tjekkes igennem igen.
		}
		else break;
	}
}

void Deframe::decodeCRC8()										// P� pr�cist samme m�de som i Inframe XOR'es der med den samme divisor hele vejen gennem bitstrengen.
{
	string bitStringCopy = bitString;
	string divisor = "100000111";

	for (int i = 0; i < bitStringCopy.length() - 8; i++)		//S� l�nge dataword indeholder andet end 0'ere, k�r statements
	{
		if (bitStringCopy[i] != '0')
		{
			string s = bitStringCopy.substr(i, 9);
			string result = "000000000";
			for (int n = 0; n < 9; n++)
			{
				result[n] = ((s[n] - '0') ^ (divisor[n] - '0')) + '0';
			}
			bitStringCopy.replace(i, 9, result);
		}
	}
	string remainder = bitStringCopy.substr(bitStringCopy.length() - 8, 8);
	bitString.erase(bitString.length() - 8, 8);					// Remainderen p� 8 bit fjernes fra bitstring.

	if (remainder == "00000000")								// Hvis remainderen = 0 findes der ingen fejl og analysen forts�tter.
	{
		checkAddresses();
	}
	else
	{
		receiveSuccess = false;									// Hvis ikke er framet fejlfyldt og recieveSuccess = false, og analysen stopper her.
		return;
	}
}

void Deframe::checkAddresses()									// Adresserne tjekkes.
{
	thisAddress = bitString.substr(0, 4);
	otherAddress = bitString.substr(4, 4);
	Addresses* addrs = Addresses::getInstance();
	
	if (addrs->getOtherAddress() != "")
	{
		if (thisAddress != addrs->getThisAddress() || otherAddress != addrs->getOtherAddress())
		{
			receiveSuccess = false;
			return;
		}
	}
	else
	{
		if (thisAddress != addrs->getThisAddress())
		{
			receiveSuccess = false;
			return;
		}
	}
	receiveSuccess = true;										// Hvis CRC- og adressetjek godkendes er pakken til os og deframing forts�tter.
	bitString.erase(0, 8);
	checkControl();
}

void Deframe::checkControl()									// Controlbittene tjekkes igennem, og informationerne overf�res til v�rdier som kan hentes af Receive-klassen.
{
	lastFrame = bitString[4];
	bitset<3> frmno(bitString.substr(5, 3));
	frameNo = frmno.to_ulong();

	if (bitString[0] == '0')									// if (I-frame)
	{
		frameType = 'I';
		bitString.erase(0, 8);									// Efter kontrolinformationerne fjernes alt andet en data-delen der skal videre til App-laget.
		compressToAscii();
	}
	else if (bitString[0] == '1')								// if (S-frame)
	{
		frameType = 'S';										// Da der ikke er noget data i et S-frame stopper analysen her.						
	}
}

void Deframe::compressToAscii()									// Strengen af bin�re v�rdier overs�ttes til ascii-karakterer til den endelige fil.
{
	stringstream sstream(bitString);
	char c;
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;

		c = char(bits.to_ulong());
		asciiDataBit += c;
	}
	asciiDataBit.erase(asciiDataBit.length() - 1, 1);
}

string Deframe::getBitString()									//Debugging
{
	return bitString;
}

string Deframe::getAsciiDataBit()
{
	return asciiDataBit;
}

string Deframe::getThisAddress()
{
	return thisAddress;
}

string Deframe::getOtherAddress()
{
	return otherAddress;
}

char Deframe::getFrameType()
{
	return frameType;
}

int Deframe::getFrameNo()
{
	return frameNo;
}

char Deframe::getLastFrame()
{
	return lastFrame;
}

bool Deframe::getReceiveSuccess()
{
	return receiveSuccess;
}

Deframe::~Deframe()
{}
