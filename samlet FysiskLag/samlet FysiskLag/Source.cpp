#include <SFML/Audio.hpp>
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
#include <chrono>
#include <array>

#include "StreamRecorder.h"
#include "PlayDTMF.h"
#include "recordDTMF.h"
#include "recordDTMFToFile.h"
#include "Buffer.h"
#include "DTMFDecode.h"

using namespace sf;
using namespace std;


void DeviceSettings()//P2A
{
	if (SoundRecorder::isAvailable())
	{

		vector<string> deviceNameList = SoundRecorder::getAvailableDevices();
		cout << "This is the list of your " << deviceNameList.size() << " available devices: " << endl;
		for (int i = 0; i < deviceNameList.size(); i++)
		{
			cout << i << ": " << deviceNameList[i] << endl;

		}

		cout << endl << "Current device is: " << SoundRecorder::getDefaultDevice() << endl;
	}
	else
		cout << "There are no devices available" << endl; // simplel fejlmeddelelse
		//throw "There are no devices available";// knap så simplel


}

void write(vector<double> data)
{
	ofstream file("data"+to_string(time(0))+".txt");
	if (file.is_open())
	{
		for (int i = 0; i < data.size(); i++)
		{
			file << data[i] << "\n";
		}

	}
	file.close();
}

vector<double> readSignal(string path)
{
	vector<double> returnVector;
	string line;
	ifstream file(path);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			returnVector.push_back(stod(line));
		}

	}
	file.close();
	return returnVector;
}

int main() 
{
	/*
	{
		DeviceSettings();
		thread recond;
		thread decode;
		bool debug = true;

		DTMFDecode * dtmfdecode = new DTMFDecode(160, debug);
		decode = thread(&DTMFDecode::decode, dtmfdecode);
		StreamRecorder * streamreconder = new StreamRecorder();
		recond = thread(&StreamRecorder::startStreamRecorder, streamreconder, 60000);

		//sleep(sf::seconds(1));
		//PlayDTMF().play2("C0FFE");

		recond.join();
		cout << "stop reconding" << endl;

		dtmfdecode->stop();
		decode.join();

		if (debug)
			write(dtmfdecode->getDebugData());

	}
	*/
	
	vector<double> signal = readSignal("C:/Users/Bruger/Desktop/data1541757433.txt");
	if (signal.size() % 160 != 0)
	{
		while (signal.size() % 160 != 0)
			signal.push_back(0);
	}

	cout << "Signal size: " << signal.size() << endl;

	clock_t start = clock();
	thread decode;
	thread decode2;

	DTMFDecode * dtmfdecode = new DTMFDecode(160, 4, false);
	decode = thread(&DTMFDecode::begin_analyse_test, dtmfdecode, signal);
	decode2 = thread(&DTMFDecode::decode_test, dtmfdecode);

	decode.join();
	decode2.join();
	clock_t stop = clock();

	cout << "Det tog " << float(stop - start) / CLOCKS_PER_SEC << " s" << endl;

	system("pause");
}

