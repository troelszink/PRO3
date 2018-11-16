#pragma once
using namespace std;
#include "Addresses.h"
#include <string>
#include <iostream>
#include <bitset>
#include <sstream>


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
	void recoverDataBit();
	void compressToAscii();

	string getBitString();
	string getAsciiDataBit();
	string getThisAddress();
	string getOtherAddress();
	
	char getFrameType();
	int getFrameNo();
	bool getLastFrame();
	bool getReceiveSuccess();

	~Deframe();
private:
	int frameNo;
	
	char frameType;

	string asciiString;
	string bitString;
	string dataBit;
	string asciiDataBit;
	string thisAddress;
	string otherAddress;

	bool lastFrame;
	bool receiveSuccess;
};

