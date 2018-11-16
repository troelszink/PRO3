#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>
#include <mutex>
#include <string>
#include <array>
#include <vector>

#include "Buffer.h"
#include "AudioAnalysis.h"
#include "AudioSample.h"

using namespace sf;
using namespace std;


class DTMFDecode 
{
public:
	DTMFDecode(int sizeWindow);
	DTMFDecode(int sizeWindow, bool Debug);
	void decode();
	void stop();
	vector<double> getDebugData();
	~DTMFDecode();
private:
	void setup();

	AudioAnalysis analyser;
	vector<double> window;
	vector<double> debugData;
	int windowSize;
	bool debug;
	bool analyseStop;
	bool bufferEmpty;

};

