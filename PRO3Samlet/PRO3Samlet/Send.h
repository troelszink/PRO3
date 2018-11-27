#pragma once
using namespace std;
#include <vector>
#include <string>
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <bitset>
#include "Buffer.h"
#include "Addresses.h"

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

