#include<thread>
#include "DTMFDecode.h"
#include "StreamRecorder.h"
#include "PlayDTMF.h"

#pragma once
class InitFysikLag
{
public:
	InitFysikLag();
	void run();
	~InitFysikLag();
private:
	thread decode;
	thread record;
	thread send;
};

