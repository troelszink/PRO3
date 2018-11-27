#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>
#include <mutex>
#include <string>
#include <array>
#include <vector>
#include <thread>
#include <future>

#include "Buffer.h"
#include "AudioAnalysis.h"

using namespace sf;
using namespace std;


class DTMFDecode 
{
public:
	DTMFDecode(int sizeWindow, unsigned short int pointSiz);
	DTMFDecode(int sizeWindow, unsigned short int pointSiz, bool Debug);

	void decode();
	void decode_test();
	void begin_analyse();
	void begin_analyse_test(vector<double> data);
	void stop();
	vector<double> getDebugData();
	~DTMFDecode();

	void add_analyseBuffer(vector<double> window);
	unsigned short int take_analyseBuffer();
private:
	void setup();

	unsigned short int point;
	vector<unsigned short int> confirm;
	unsigned short int pointSize;

	AudioAnalysis analyser;
	vector<double> window;
	vector<double> debugData;

	future<unsigned short int> analyse[10];
	unsigned short int pointerInd;
	unsigned short int pointerOut;
	unsigned short int size;
	mutex mutex_analyse;

	int windowSize;
	bool debug;
	bool testDone;
	bool testDone2;
	bool analyseStop;

};

