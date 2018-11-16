#pragma once
using namespace std;
//#include "Receive.h"
//#include "Inframe.h"
//#include "Deframe.h"
#include "Buffer.h"
#include "Addresses.h"
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <bitset>

class Send
{
public:
	Send();
	~Send();

	void sendFrames(vector<string>, string);
	void frameToBuffer(string);

private:
	int frameCnt;
	int timerLength;
	int maxAttempts;

	string thisAddress;
	string otherAddress;
	vector<string> frameVector;
	Buffer* buff;
	Addresses* addrs;
};

