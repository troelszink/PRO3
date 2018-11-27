#pragma once
using namespace std;
#include <string>
#include <iostream>
#include <bitset>
#include <sstream>
#include "Addresses.h"

class Deframe
{
public:
	Deframe();
	Deframe(string, string, string);

	void runDeframe();
	void deflag();
	void bitdestuffing();
	void decodeCRC8();
	void checkAddresses();
	void checkControl();
	void compressToAscii();

	string getBitString();
	string getAsciiDataBit();
	string getThisAddress();
	string getOtherAddress();
	
	int getFrameNo();
	char getFrameType();
	char getLastFrame();
	bool getReceiveSuccess();

	~Deframe();

private:
	int frameNo;
	char frameType;
	char lastFrame;
	bool receiveSuccess;

	string asciiString;
	string bitString;
	string dataBit;
	string asciiDataBit;
	string thisAddress;
	string otherAddress;
};

