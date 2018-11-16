#include "KOMinit.h"



KOMinit::KOMinit()
{
	buff = Buffer::getInstance();
	thread t1(this->sendThread);
	thread t2(this->receiveThread);
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
		rec.receiveBits(buff->takeFrom_datalinkToSound());
	}
}

void KOMinit::sendThread()
{
	while (true)
	{
		string stringToSend = buff->takeFrom_appToDatalink();
		InframeArchive toSend(stringToSend);
		toSend.sendFrames();
	}
	
}
