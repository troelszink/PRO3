#include "KOMinit.h"

KOMinit::KOMinit()
{
	buff = Buffer::getInstance();
	thread t1(&KOMinit::sendThread, this);
	thread t2(&KOMinit::receiveThread, this);
	t1.join();
	t2.join();
}

KOMinit::~KOMinit()
{}

void KOMinit::receiveThread()
{
	Receive rec;
	while (true)
	{
		try
		{
			rec.receiveBits(buff->takeFrom_soundToDatalink());
		}
		catch (...)
		{
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		if (buff->checkFlag(0))
			break;
	}
}

void KOMinit::sendThread()
{
	while (true)
	{
		try
		{
			string stringToSend = buff->takeFrom_appToDatalink();
			InframeArchive toSend(stringToSend);
			toSend.sendFrames();
		}
		catch (...)
		{
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		if (buff->checkFlag(0))
			break;
	}
}
