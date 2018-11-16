#include "Addresses.h"

Addresses* Addresses::instance = 0;						// Første gang instansen oprettes initialiseres "instance" til at være , og static gør at denne værdi gemmes på tværs af instanser.

Addresses* Addresses::getInstance()						// Denne metode kaldes når der oprettes instanser af klassen.
{
	if (instance == 0)									// Hvis det er første gang oprettes en ny instans, kaldes constructoren på ny, og instance-pointeren gemmes til instansens memory-adresse. 
	{
		instance = new Addresses();
	}
	return instance;									// Hvis det ikke er første gang henvises der til den eksisterende instans i hukommelsen.
}

Addresses::Addresses()									// Denne constructor er private, så andre klasser ikke blot kan oprette nye instanser.
{
	thisAddress = "0000";								// thisAddress sættes til 0000, hvilket er server-adressen. Hvis enheden er klient sættes der en ny thisAddress første gang der sendes noget.
	otherAddress = "";									// otherAddress gemmes først når der sendes eller modtages noget for første gang. 
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
