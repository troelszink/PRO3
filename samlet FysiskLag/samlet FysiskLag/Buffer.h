#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <exception>
#include <fstream>
#include <iterator>
#include <thread>
#include <bitset>
#include "SFML/Audio.hpp"

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

private:
	static Buffer* instance;
	Buffer();
	~Buffer();

	vector<double>DTMF_SlicesBufferRecive;//Er til at opbevare bider af funde og endnu ikke godkendte DTMF toner.
	vector<bitset<4>>soundToDatalink;//Er til at opbevare funde og godkendte DTMF toner.

	vector<bitset<4>>datalinkToSound;//Er til at opbevare DTMF toner, der skal afspilles.

	vector<string>appToDatalink;//(Klient perspektiv)Er til at opbevare forespørgelser fra klienten om server tjeneste.
	vector<string>datalinkToApp;//(Klient perspektiv)Er til at opbevare svar om server tjeneste til klient fra server.

	bitset<3> message;
};

