#include "Addresses.h"

Addresses* Addresses::instance = 0;						// F�rste gang instansen oprettes initialiseres "instance" til at v�re , og static g�r at denne v�rdi gemmes p� tv�rs af instanser.

Addresses* Addresses::getInstance()						// Denne metode kaldes n�r der oprettes instanser af klassen.
{
	if (instance == 0)									// Hvis det er f�rste gang oprettes en ny instans, kaldes constructoren p� ny, og instance-pointeren gemmes til instansens memory-adresse. 
	{
		instance = new Addresses();
	}
	return instance;									// Hvis det ikke er f�rste gang henvises der til den eksisterende instans i hukommelsen.
}

Addresses::Addresses()									// Denne constructor er private, s� andre klasser ikke blot kan oprette nye instanser.
{
	thisAddress = "0000";								// thisAddress s�ttes til 0000, hvilket er server-adressen. Hvis enheden er klient s�ttes der en ny thisAddress f�rste gang der sendes noget.
	otherAddress = "";									// otherAddress gemmes f�rst n�r der sendes eller modtages noget for f�rste gang. 
	ack = 0;
}

void Addresses::setThisAddress(string taddr)
{
	thisAddress = taddr;
}

void Addresses::setOtherAddress(string oaddr)
{
	otherAddress = oaddr;
}

void Addresses::setAck(int a)
{
	ack = a;
}

string Addresses::getThisAddress()
{
	return thisAddress;
}

string Addresses::getOtherAdress()
{
	return otherAddress;
}

int Addresses::getAck()
{
	return ack;
}

void Addresses::setFrameNr(int nr)
{
	frameNr = nr;
}

int Addresses::getFrameNr()
{
	return frameNr;
}

Addresses::~Addresses()
{}
