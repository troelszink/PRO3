#pragma once
using namespace std;
#include "Inframe.h"
#include "Deframe.h"
#include "Buffer.h"
#include "Addresses.h"
#include <iostream>
#include <bitset>

class Receive
{
public:
	Receive();
	~Receive();

	void receiveBits(bitset<4>);
	void interpret(string);

private:
	int minFrameLength;
	int frameCnt;

	string bitstream;
	string receivedFrame;
	string asciiFile;
	string thisAddress;
	string otherAddress;

	Buffer* buff;
	Addresses* addrs;
};

