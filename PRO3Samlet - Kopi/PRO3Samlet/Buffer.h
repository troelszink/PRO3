#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <mutex>
#include <exception>
#include <fstream>
#include <iterator>
#include <thread>
#include <bitset>

using namespace std;
class Buffer
{
public:
	static Buffer* getInstance();

	void addToDTMF_SlicesBufferRecive(double newElemnt);
	double takeFromDTMF_SlicesBufferRecive();

	void addTo_soundToDatalink(bitset<4> newElemnt);
	bitset<4> takeFrom_soundToDatalink();

	void addTo_datalinkToSound(bitset<4> newElemnt);
	bitset<4> takeFrom_datalinkToSound();

	void addTo_appToDatalink(string newstring);
	string takeFrom_appToDatalink();

	void addTo_datalinkToApp(string newstring);
	string takeFrom_datalinkToApp();

	void setFlag(int index, bool state);
	bool checkFlag(int index);


	void printBuffer(int);
	int getBufferLength(int);

	string getBufferElement(int buffer, int i);

private:
	static Buffer* instance;
	char bit2hex(bitset<4> bit);
	
	Buffer();
	~Buffer();

	// Slicebuffer
	
	double DTMF_SlicesBufferRecive[480000];//Er til at opbevare bider af funde og endnu ikke godkendte DTMF toner.
	int DTMF_Slices_maxSize = 480000;
	int DTMF_Slices_nextIn = 0;
	int DTMF_Slices_nextOut = 0;
	int DTMF_Slices_size = 0;
	mutex DTMF_sliceMutex;
	
	
	bitset<4> soundToDatalink_buffer[20];//Er til at opbevare bider af funde og endnu ikke godkendte DTMF toner.
	int soundToDatalink_maxSize = 20;
	int soundToDatalink_nextIn = 0;
	int soundToDatalink_nextOut = 0;
	int soundToDatalink_size = 0;
	mutex soundToDatalink_mutex;

	bitset<4> datalinkToSound_buffer[20];//Er til at opbevare bider af funde og endnu ikke godkendte DTMF toner.
	int datalinkToSound_maxSize = 20;
	int datalinkToSound_nextIn = 0;
	int datalinkToSound_nextOut = 0;
	int datalinkToSound_size = 0;
	mutex datalinkToSound_mutex;

	string appToDatalink_buffer[7]; //(Klient perspektiv)Er til at opbevare forespørgelser fra klienten om server tjeneste.
	int appToDatalink_maxSize = 7;
	int appToDatalink_nextIn = 0;
	int appToDatalink_nextOut = 0;
	int appToDatalink_size = 0;
	mutex appToDatalink_mutex;

	string datalinkToApp_buffer[2]; //(Klient perspektiv)Er til at opbevare svar om server tjeneste til klient fra server.
	int datalinkToApp_maxSize = 2;
	int datalinkToApp_nextIn = 0;
	int datalinkToApp_nextOut = 0;
	int datalinkToApp_size = 0;
	mutex datalinkToApp_mutex;


	bitset<4> message; // message;
};

