#include "KOMinit.h"



KOMinit::KOMinit()
{
	buff = Buffer::getInstance();
	thread t1(&KOMinit::receiveThread,this);
	thread t2(&KOMinit::sendThread,this);
	t1.join();
	t2.join();
}


KOMinit::~KOMinit()
{}

void KOMinit::run()
{

	buff = Buffer::getInstance();
	thread t1(&KOMinit::receiveThread, this);
	thread t2(&KOMinit::sendThread, this);
	t1.join();
	t2.join();
}

void KOMinit::receiveThread()
{
	Receive rec;
	while (true)
	{
		rec.receiveBits(buff->takeFrom_datalinkToSound());
		if (buff->checkFlag(0))
			break;
	}
}

void KOMinit::sendThread()
{
	while (true)
	{
		string stringToSend = buff->takeFrom_appToDatalink();
		InframeArchive toSend(stringToSend);
		toSend.sendFrames();

		if (buff->checkFlag(0))
			break;
	}
	
}
