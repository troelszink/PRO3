#include "DSPMath.h";
#include<bitset>
#include<array>
#include <iostream>
#include <fstream>
#include "ParelleFilter.h"

using namespace std;
#pragma once
class AudioAnalysis
{
public:
	enum filterActive { None, Basic, Advancdes };

	AudioAnalysis();
	AudioAnalysis(int thresTone, int sampleRate, int hexthreshold, int Padding,  unsigned short int pointsize,int amplThreshold,filterActive filter);
	void analysis(vector<double> signal);
	void analysis(vector<double>, bool test);
	vector<int> frequencyInSignal2(vector<complex<double>> signal);
	unsigned short int findTones2(vector<double> splitSignal);
	void sendTone(unsigned short int index);
	unsigned short int findTones(vector<double> splitSignal);
	
	vector<double> filter(vector<double> signal);
	vector<int> frequencyInSignal(vector<complex<double>> signal);
	bool mean(vector<double> signal);
	vector<double> removeBelow(vector<double> signal);

	void setFilter(filterActive fActive);
	vector<int> getTones();
	~AudioAnalysis();
private:
	void setup();
	void read(string file);

	filterActive active;
	vector<ParelleFilter> filters;

	int thresholdForTone;
	int samplerate;
	int hexThreshold;
	int padding;
	int amplitudeThreshold;

	unsigned short int pointSize;
	unsigned short int point;
	vector<unsigned short int> confirm;
	vector<int> tones;

	vector<int> mValues;
	vector<int> freqValues;
};

