#pragma once
using namespace std;
#include <string>
#include <bitset>
#include <iostream>
#include <sstream>

class Inframe
{
public:
	Inframe();
	Inframe(string, int, int, char, string);
	void runInframe();
	void expandToBinary();
	void addControl();
	void addAddresses();
	void encodeCRC8();
	void bitstuffing();
	void addFlag();
	void addExtraZeroes();
	void compressToAscii();
	string getFinalFrame();
	string getDataBit();
	~Inframe();

private:
	int frameType;
	int frameNo;
	char lastFrame;
	string dataBit;
	string asciiDataBit;
	string frame;
	string finalFrame;
	string addresses;
	string flag;
};

