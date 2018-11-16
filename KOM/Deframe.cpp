#include "Deframe.h"

Deframe::Deframe()
{
}

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

void Deframe::bitdestuffing()									// Fjerner de ekstra 0'er der indsættes i tilfælde af utilsigtet flag.
{
	int i = 0;
	while (i < bitString.length())
	{
		if (bitString.find("111110", i) != string::npos)		// bitstring tjekkes igennem efter bitstuffing-sekvensen, og fjerner de ekstra 0 der blev tilføjet.
		{
			int pos = bitString.find("111110", i);
			bitString.erase(pos + 5, 1);
			i = pos + 5;										// Indekset placeres efter sekvensen og der tjekkes igennem igen.
		}
		else
			break;
	}
}

void Deframe::decodeCRC8()										// På præcist samme måde som i Inframe XOR'es der med den samme divisor hele vejen gennem bitstrengen.
{
	string bitStringCopy = bitString;
	string divisor = "100000111";

	for (int i = 0; i < bitStringCopy.length() - 8; i++)		//Så længe dataword indeholder andet end 0'ere, kør statements
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
	bitString.erase(bitString.length() - 8, 8);					// Remainderen på 8 bit fjernes fra bitstring.

	if (remainder == "00000000")								// Hvis remainderen = 0 findes der ingen fejl og receiveSuccess = true, og analysen fortsætter.
	{
		receiveSuccess = true;
		checkAddresses();
	}
	else
	{
		receiveSuccess = false;									// Hvis ikke er framet fejlfyldt og recieveSuccess = false, og analysen stopper her.
	}
}

void Deframe::checkAddresses()									// Adresserne tjekkes.
{
	thisAddress = bitString.substr(0, 4);
	otherAddress = bitString.substr(4, 4);
	Addresses* addrs = Addresses::getInstance();
	
	if (addrs->getOtherAdress() != "")
	{
		if (thisAddress != addrs->getThisAddress() || otherAddress != addrs->getOtherAdress())
		{
			receiveSuccess = false;
		}
	}
	else
	{
		if (thisAddress != addrs->getThisAddress())
		{
			receiveSuccess = false;
		}
	}
	bitString.erase(0, 8);
	//if (receiveSuccess)
		//cout << "checkAddresses done: " << bitString << "               " << bitString.length() << endl;
	checkControl();
}

void Deframe::checkControl()									// Controlbittene tjekkes igennem, og informationerne overføres til værdier som kan hentes af Transmission-klassen.
{
	cout << "Control: " << bitString.substr(0, 8) << endl;
	if (bitString[0] == '0')									// if (I-frame)
	{
		frameType = 'I';
		bitset<3> frmno(bitString.substr(1, 3));
		frameNo = frmno.to_ulong();
		
		if (bitString[4] == '1')
		{
			lastFrame = true;
		}
		else
		{
			lastFrame = false;
		}
		recoverDataBit();										// Efter kontrolinformationerne fjernes alt andet en data-delen der skal videre til App-laget.
		compressToAscii();
	}
	else if (bitString.substr(0, 2) == "10")					// if (S-frame)
	{
		frameType = 'S';
		bitset<3> frmno(bitString.substr(5, 3));
		frameNo = frmno.to_ulong();

		if (bitString[4] == '1')
		{
			lastFrame = true;
		}
		else
		{
			lastFrame = false;
		}														// Da der ikke er noget data i et S-frame stopper analysen her.
	}
}

void Deframe::recoverDataBit()									// Controlbittene fjernes så der kun er data-sektionen tilbage.
{
	bitString.erase(0, 8);
}

void Deframe::compressToAscii()									// På samme måde som i Inframe komprimeres stringen af binære værdier til ascii-karakterer for at mindske hukommelsesforbruget.
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

string Deframe::getBitString()
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

bool Deframe::getLastFrame()
{
	return lastFrame;
}

bool Deframe::getReceiveSuccess()
{
	return receiveSuccess;
}

Deframe::~Deframe()
{
}
