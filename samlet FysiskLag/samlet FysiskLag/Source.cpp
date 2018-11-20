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


int main() 
{
	DeviceSettings();
	thread recond;
	thread decode;
	bool debug = true;

	DTMFDecode * dtmfdecode = new DTMFDecode(160,debug);
	decode = thread(&DTMFDecode::decode, dtmfdecode);
	StreamRecorder * streamreconder = new StreamRecorder();
	recond = thread(&StreamRecorder::startStreamRecorder,streamreconder,60000);

	//sleep(sf::seconds(1));
	//PlayDTMF().play2("C0FFE");

	recond.join();
	cout << "stop reconding" << endl;

	dtmfdecode->stop();
	decode.join();

	if (debug)
		write(dtmfdecode->getDebugData());	


	system("pause");
}

