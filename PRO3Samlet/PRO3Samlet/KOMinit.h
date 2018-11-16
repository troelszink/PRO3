#pragma once
#include <thread>
#include "Buffer.h"
#include "InframeArchive.h"
#include "Receive.h"

class KOMinit
{
public:
	KOMinit();
	~KOMinit();

	void run();
	void receiveThread();
	void sendThread();

private:
	Buffer* buff;
	//thread receive;
	//thread send;
};

