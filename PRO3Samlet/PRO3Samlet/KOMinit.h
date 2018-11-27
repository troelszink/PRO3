#pragma once
#include <thread>
#include "InframeArchive.h"
#include "Receive.h"

class KOMinit
{
public:
	KOMinit();
	~KOMinit();

	void receiveThread();
	void sendThread();

private:
	Buffer* buff;
};

