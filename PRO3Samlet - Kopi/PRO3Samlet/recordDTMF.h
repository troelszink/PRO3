#pragma once
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <exception>
#include <fstream>
#include <iterator>


using namespace sf;
using namespace std;

class recordDTMF //P5C, optager til buffer, laver en vektor af dataet, som gemmes som en .txt fil, der kan bruges i matlab
{
public:
	recordDTMF();
	void record(int aRecTime);//(int aRecTime, bool print);
	~recordDTMF();
	
private:
	int recTime;
};

