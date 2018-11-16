#pragma once
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <bitset>
#include "Buffer.h"

using namespace std;

class PlayDTMF
{
public:
	PlayDTMF();
	
	void handler();
	char bit2hex(bitset<4> bit);
	
	//PlayDTMF(std::string aDigit, unsigned aDuration);
	void play2(std::string aDigit);
	//PlayDTMF(char aDigit);
	//unsigned getSampleRate();
	//double getFreq(int);

		void genBuffer();
	~PlayDTMF();

private:
	void play();
	unsigned durationPlay;
	sf::Int16* raw;
	unsigned sampleRate=8000;
	unsigned amp=15000;
	double freqs[2];
	sf::SoundBuffer* buffer;
	sf::Sound* sound;
	std::string inString;
	//void genBuffer();

};

