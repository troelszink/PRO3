#include "DSPMath.h"
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
	AudioAnalysis(int thresTone, int sampleRate, int hexthreshold, int Padding,int amplThreshold,filterActive filter);

	unsigned short int analysis(vector<double> signal); // Hoved funktion til at analysere et givet signal

	void sendTone(unsigned short int index); // Godkendte toner videre

	unsigned short int findTones(vector<double> splitSignal); // Finder hvilken tones som finde optager i signalet
	
	vector<double> filter(vector<double> signal); // bruges til at filterer signalet
	vector<int> frequencyInSignal(vector<complex<double>> signal); // Finder hvilken lav og høje frekvens som dominere mestet i signalet
	bool mean(vector<double> signal); // returner true hvis signalet middel værdi er over en bestemt threshold. 
	vector<double> removeBelow(vector<double> signal); // Fjerne værdierne under en bestemt threshold

	void setFilter(filterActive fActive); // Skrifter hvilken filter som skal være aktivere
	vector<int> getTones(); // Returner listen tones, det er kun beregnet til test.
	
	~AudioAnalysis();
private:
	void setup(); // Bruges til at sætte filter op
	void read(string file); // Indlæser filter værdier

	filterActive active; // Angivere hvilken filter niveau som analyseren bruger
	vector<ParelleFilter> filters; // Indeholder de forskellige filter

	int thresholdForTone; // den threshold som skal overstiger for at det er en godkendte frekvens som kan tages med i betragning til hvilken tone som findes i signalet.
	int samplerate; // Angiver hvor hurtige det samples
	int hexThreshold; // Angiver for stå anvigelse frekvenser må have for de rigtige DTMF frekvenser får de acceptere som DTMF
	int padding; // Hvor meget man skal zero padder med
	int amplitudeThreshold; // Angiver minimum middel værdien for signalet bliver arbejde videre med. 

	unsigned short int pointSize;
	unsigned short int point;
	vector<unsigned short int> confirm;
	vector<int> tones;

	vector<int> mValues;
	vector<int> freqValues;
};

