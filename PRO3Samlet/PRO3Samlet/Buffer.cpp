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
{}

void Buffer::addToDTMF_SlicesBufferRecive(double newElemnt)
{
	if (DTMF_Slices_size >= DTMF_Slices_maxSize)
		throw "wait";

	DTMF_SlicesBufferRecive[DTMF_Slices_nextIn] = newElemnt;
	DTMF_Slices_nextIn = (DTMF_Slices_nextIn + 1) % DTMF_Slices_maxSize;
	DTMF_Slices_nextOut;
	DTMF_sliceMutex.lock();
	DTMF_Slices_size++;
	DTMF_sliceMutex.unlock();

}

double Buffer::takeFromDTMF_SlicesBufferRecive()
{
	if (DTMF_Slices_size == 0)
		throw "wait";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	double returnValue = DTMF_SlicesBufferRecive[DTMF_Slices_nextOut];//Kopierer elementet, inden det slettes. 
	DTMF_Slices_nextOut = (DTMF_Slices_nextOut + 1) % DTMF_Slices_maxSize;
	DTMF_sliceMutex.lock();
	DTMF_Slices_size--;
	DTMF_sliceMutex.unlock();
	return returnValue;
}

void Buffer::addTo_soundToDatalink(bitset<4> newElemnt)
{
	if (soundToDatalink_size == soundToDatalink_maxSize)
		throw "wait";

	cout << bit2hex(newElemnt) << " ";
	soundToDatalink_buffer[soundToDatalink_nextIn] = newElemnt;
	soundToDatalink_nextIn = (soundToDatalink_nextIn + 1) % soundToDatalink_maxSize;

	soundToDatalink_mutex.lock();
	soundToDatalink_size++;
	soundToDatalink_mutex.unlock();
}

bitset<4> Buffer::takeFrom_soundToDatalink()
{
	if (soundToDatalink_size == 0)
		throw "wait";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	bitset<4> returnValue = soundToDatalink_buffer[soundToDatalink_nextOut];//Kopierer elementet, inden det slettes. 
	soundToDatalink_nextOut = (soundToDatalink_nextOut + 1) % soundToDatalink_maxSize;
	soundToDatalink_mutex.lock();
	soundToDatalink_size--;
	soundToDatalink_mutex.unlock();
	return returnValue;
}

void Buffer::addTo_datalinkToSound(bitset<4> newElemnt)
{
	if (datalinkToSound_size == datalinkToSound_maxSize)
		throw "wait";

	datalinkToSound_buffer[datalinkToSound_nextIn] = newElemnt;
	datalinkToSound_nextIn = (datalinkToSound_nextIn + 1) % datalinkToSound_maxSize;

	datalinkToSound_mutex.lock();
	datalinkToSound_size++;
	datalinkToSound_mutex.unlock();
}

bitset<4> Buffer::takeFrom_datalinkToSound()
{
	if (datalinkToSound_size == 0)
		throw "wait";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	bitset<4> returnValue = datalinkToSound_buffer[datalinkToSound_nextOut];//Kopierer elementet, inden det slettes. 
	datalinkToSound_nextOut = (datalinkToSound_nextOut + 1) % datalinkToSound_maxSize;
	datalinkToSound_mutex.lock();
	datalinkToSound_size--;
	datalinkToSound_mutex.unlock();
	return returnValue;
}

void Buffer::addTo_appToDatalink(string newElemnt)
{
	if (appToDatalink_size == appToDatalink_maxSize)
		throw "wait";

	appToDatalink_buffer[appToDatalink_nextIn] = newElemnt;
	appToDatalink_nextIn = (appToDatalink_nextIn + 1) % appToDatalink_maxSize;

	appToDatalink_mutex.lock();
	appToDatalink_size++;
	appToDatalink_mutex.unlock();
}

string Buffer::takeFrom_appToDatalink()
{
	if (appToDatalink_size == 0)
		throw "wait";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	string returnValue = appToDatalink_buffer[appToDatalink_nextOut];//Kopierer elementet, inden det slettes. 
	appToDatalink_nextOut = (appToDatalink_nextOut + 1) % appToDatalink_maxSize;
	appToDatalink_mutex.lock();
	appToDatalink_size--;
	appToDatalink_mutex.unlock();
	return returnValue;
}


void Buffer::addTo_datalinkToApp(string newElemnt)
{
	
	if (datalinkToApp_size == datalinkToApp_maxSize)
		throw "wait";

	datalinkToApp_buffer[datalinkToApp_nextIn] = newElemnt;
	datalinkToApp_nextIn = (datalinkToApp_nextIn + 1) % datalinkToApp_maxSize;

	datalinkToApp_mutex.lock();
	datalinkToApp_size++;
	datalinkToApp_mutex.unlock();
}

string Buffer::takeFrom_datalinkToApp()
{
	if (datalinkToApp_size == 0)
		throw "wait";//metode til Joakim og Andreas, try & catch.
					  //cout << DTMFVector.size() <<endl;
	string returnValue = datalinkToApp_buffer[datalinkToApp_nextOut];//Kopierer elementet, inden det slettes. 
	datalinkToApp_nextOut = (datalinkToApp_nextOut + 1) % datalinkToApp_maxSize;
	datalinkToApp_mutex.lock();
	datalinkToApp_size--;
	datalinkToApp_mutex.unlock();
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

void Buffer::printBuffer(int s)
{
	//if (s == 1)
	//	for (int i = 0; i < soundToDatalink.size(); i++)
	//	{
	//		cout << soundToDatalink[i].to_string() << endl;
	//	}
	//else if (s == 2)
	//	for (int i = 0; i < datalinkToSound.size(); i++)
	//	{
	//		cout << datalinkToSound[i].to_string() << endl;
	//	}
	//else if (s == 3)
	//	for (int i = 0; i < appToDatalink.size(); i++)
	//	{
	//		cout << appToDatalink[i] << endl;
	//	}
	//else if (s == 4)
	//	for (int i = 0; i < datalinkToApp.size(); i++)
	//	{
	//		cout << datalinkToApp[i] << endl;
	//	}
}

int Buffer::getBufferLength(int s)
{
	//if (s == 1)
	//	return soundToDatalink.size();
	//else if (s == 2)
	//	return datalinkToSound.size();
	//else if (s == 3)
	//	return appToDatalink.size();
	//else if (s == 4)
	//	return datalinkToApp.size();
	return -1;
}

string Buffer::getBufferElement(int buffer, int i)
{
	//switch (buffer)
	//{
	//	case 3:
	//		return appToDatalink[i];
	//	case 4:
	//		return datalinkToApp[i];
	//}
	return "";
}

char Buffer::bit2hex(bitset<4> bit)
{
	if (bit == 0)
		return '0';
	else if (bit == 1)
		return '1';
	else if (bit == 2)
		return '2';
	else if (bit == 3)
		return '3';
	else if (bit == 4)
		return '4';
	else if (bit == 5)
		return '5';
	else if (bit == 6)
		return '6';
	else if (bit == 7)
		return '7';
	else if (bit == 8)
		return '8';
	else if (bit == 9)
		return '9';
	else if (bit == 10)
		return 'A';
	else if (bit == 11)
		return 'B';
	else if (bit == 12)
		return 'C';
	else if (bit == 13)
		return 'D';
	else if (bit == 14)
		return 'E';
	else if (bit == 15)
		return 'F';
}

Buffer::~Buffer()
{}
