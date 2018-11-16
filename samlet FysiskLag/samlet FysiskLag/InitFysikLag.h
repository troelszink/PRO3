#include<thread>
#include "DTMFDecode.h"
#include "StreamRecorder.h"
#include "PlayDTMF.h"

#pragma once
class InitFysikLag
{
public:
	InitFysikLag();
	~InitFysikLag();
private:
	thread decode;
	thread record;
	thread send;
};

