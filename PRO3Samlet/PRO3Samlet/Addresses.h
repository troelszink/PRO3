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
	void setFrameNo(int);

	string getThisAddress();
	string getOtherAddress();

	int getAck();
	int getFrameNo();

	~Addresses();

private:
	static Addresses* instance;
	Addresses();

	string thisAddress;
	string otherAddress;

	int ack;
	int frameNo;
};

