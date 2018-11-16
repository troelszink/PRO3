#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>
#include <mutex>

using namespace sf;
using namespace std; 

class recordDTMFToFile
{

public:
		recordDTMFToFile(int aTime);
		//void PlayFromFile(string aFileName);
		~recordDTMFToFile();
private:
		int recTime;
	
};

