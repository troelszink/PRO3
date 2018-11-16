#include "Buffer.h"

Buffer* Buffer::instance = 0;

Buffer* Buffer::getInstance()
{
	if (instance == 0)
	{
		instance = new Buffer();
	}
	return instance;
}

Buffer::Buffer()
{
	message = 0;
}

void Buffer::addToDTMF_SlicesBufferRecive(double newElemnt)
{
	DTMF_SlicesBufferRecive.push_back(newElemnt);
}

double Buffer::takeFromDTMF_SlicesBufferRecive()
{
	if (DTMF_SlicesBufferRecive.size() == 0)
		throw "Empty";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	double returnValue = DTMF_SlicesBufferRecive[0];//Kopierer elementet, inden det slettes. 
	DTMF_SlicesBufferRecive.erase(DTMF_SlicesBufferRecive.begin());
	return returnValue;
}




void Buffer::addTo_soundToDatalink(bitset<4> newElemnt)
{
	soundToDatalink.push_back(newElemnt);
}

bitset<4> Buffer::takeFrom_soundToDatalink()
{
	if (soundToDatalink.size() == 0)
	{
		throw "Empty";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	}
	bitset<4> returnValue = soundToDatalink[0];//Kopierer elementet, inden det slettes. 
	soundToDatalink.erase(soundToDatalink.begin());
	return returnValue;
}

void Buffer::addTo_datalinkToSound(bitset<4> newElemnt)
{
	datalinkToSound.push_back(newElemnt);
}

bitset<4> Buffer::takeFrom_datalinkToSound()
{
	if (datalinkToSound.size() == 0)
		throw "Empty";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	bitset<4> returnValue = datalinkToSound[0];//Kopierer elementet, inden det slettes. 
	datalinkToSound.erase(datalinkToSound.begin());
	return returnValue;
}

void Buffer::addTo_appToDatalink(string newstring)
{
	appToDatalink.push_back(newstring);
}

string Buffer::takeFrom_appToDatalink()
{
	if (appToDatalink.size() == 0)
		throw "Empty";//metode til try og catch

	string returnValue = appToDatalink[0];//Kopierer elementet, inden det slettes. 
	appToDatalink.erase(appToDatalink.begin());
	return returnValue;
}


void Buffer::addTo_datalinkToApp(string newstring)
{
	datalinkToApp.push_back(newstring);
}

string Buffer::takeFrom_datalinkToApp()
{
	if (datalinkToApp.size() == 0)
		throw "Empty";//metode til try og catch.

	string returnValue = datalinkToApp[0];//Kopierer elementet, inden det slettes. 
	datalinkToApp.erase(datalinkToApp.begin());
	return returnValue;
}

void Buffer::setFlag(int index, bool state)
{
	message[index] = state;
}

bool Buffer::checkFlag(int index)
{
	return message[index];
}


Buffer::~Buffer()
{}
