#pragma once
using namespace std;
#include <string>

class Addresses
{
public:
	static Addresses* getInstance();

	void setThisAddress(string);
	void setOtherAddress(string);
	void setAck(int);
	void setFrameNr(int);

	string getThisAddress();
	string getOtherAdress();

	int getAck();
	int getFrameNr();

	~Addresses();

private:
	static Addresses* instance;
	Addresses();

	string thisAddress;
	string otherAddress;

	int ack;
	int frameNr;
};

