#pragma once
using namespace std;
#include <string>
#include <vector>
#include "Inframe.h"
#include "Send.h"
#include <iostream>
#include "Buffer.h"

class InframeArchive
{
public:
	InframeArchive();
	InframeArchive(string);

	void sendFrames();
	void extractAddresses();
	void splitAsciiString();
	void makeFrames();

	void printVector();
	~InframeArchive();

private:
	int frameType;
	int dataBitSize;

	string asciiString;
	string receiverAndSender;

	vector<string> dataBitVector;
	vector<string> frameVector;

	Buffer* buff;	
};

