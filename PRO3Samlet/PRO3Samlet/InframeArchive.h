#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include "Inframe.h"
#include "Send.h"
#include "Buffer.h"

class InframeArchive
{
public:
	InframeArchive();
	InframeArchive(string);

	void sendFrames();
	void makeFrames();
	void printVector();

	~InframeArchive();

private:
	int frameType;
	int dataBitSize;

	string asciiString;
	string receiverAndSender;

	vector<string> frameVector;

	Buffer* buff;	
};

