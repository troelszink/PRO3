#include <thread>
#include "ClientRequestReply.h"

#pragma once
class COSinitClient
{
public:
	COSinitClient();
	void run();
	~COSinitClient();
private:
	thread t1;
	thread t2;
};

