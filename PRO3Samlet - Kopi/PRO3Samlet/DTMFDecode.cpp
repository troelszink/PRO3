#include "DTMFDecode.h"



DTMFDecode::DTMFDecode(int sizeWindow, unsigned short int pointSiz)
{

	for (int i = 0; i < pointSiz; i++)
		confirm.push_back(16);

	windowSize = sizeWindow;
	pointerInd = 0;
	pointerOut = 0;
	pointSize = pointSiz;
	size = 10;
	debug = false;
	testDone = false;
	testDone2 = false;
	analyser = AudioAnalysis(10000, 8000, 10, 1024, 200, AudioAnalysis::None);
}

DTMFDecode::DTMFDecode(int sizeWindow,  unsigned short int pointSiz, bool Debug)
{
	for (int i = 0; i < pointSiz; i++)
		confirm.push_back(16);

	windowSize = sizeWindow;
	pointerInd = 0;
	pointerOut = 0;
	pointSize = pointSiz;
	size = 0;
	debug = Debug;
	testDone = false;
	testDone2 = false;
	analyser = AudioAnalysis(10000, 8000, 10, 1024, 200, AudioAnalysis::None);
}

void DTMFDecode::decode()
{
	while (!Buffer::getInstance()->checkFlag(0))
	{
		unsigned short int r = 16;
		while (true)
		{
			try
			{
				r = take_analyseBuffer();
				break;
			}
			catch (...)
			{
				sf::sleep(sf::milliseconds(20));
			}
			if (Buffer::getInstance()->checkFlag(0))
				break;
		}
		
		if (r < 16 && !Buffer::getInstance()->checkFlag(0))
		{
			if (point == 0)
				confirm[point++] = r;
			else if (confirm[0] == r)
				confirm[point++] = r;
			else
			{
				point = 0;
				confirm[point++] = r;
			}

			if (point == pointSize)
			{
				Buffer::getInstance()->addTo_soundToDatalink(confirm[0]);
				confirm[0] = 16;
				point = 0;
			}

		}
		else
		{
			confirm[0] = 16;
			point = 0;
		}
	}
}

void DTMFDecode::decode_test()
{
	while (!Buffer::getInstance()->checkFlag(0))
	{
		unsigned short int r = 16;
		while (true)
		{
			try
			{
				r = take_analyseBuffer();
				break;
			}
			catch (...)
			{
				sf::sleep(sf::milliseconds(20));
				if (testDone)
				{
					testDone2 = true;
					break;
				}
			}
		}

		if (testDone2)
			break;

		if (r < 16)
		{
			if (point == 0)
				confirm[point++] = r;
			else if (confirm[0] == r)
				confirm[point++] = r;
			else
			{
				point = 0;
				confirm[point++] = r;
			}

			if (point == pointSize)
			{
				analyser.sendTone(confirm[0]);
				confirm[0] = 16;
				point = 0;
			}

		}
		else
		{
			confirm[0] = 16;
			point = 0;
		}
	}

	vector<int> k = analyser.getTones();
	for (int l : k)
		cout << l << " ";
	cout << endl;
}

void DTMFDecode::begin_analyse()
{
	analyser = AudioAnalysis(10000, 8000, 10, 1024, 200, AudioAnalysis::None);

	while (!Buffer::getInstance()->checkFlag(0))
	{
		try
		{
			double value = Buffer::getInstance()->takeFromDTMF_SlicesBufferRecive();
			window.push_back(value);

			if (debug)
				debugData.push_back(value);

			if (window.size() == windowSize)
			{
				while (true)
				{
					try
					{
						add_analyseBuffer(window);
						break;
					}
					catch(...){
						sf::sleep(sf::milliseconds(20));
					}

					if (Buffer::getInstance()->checkFlag(0))
						break;
				}
				window.clear();
			}
		}
		catch (...)
		{
			sf::sleep(sf::milliseconds(20));

		}
	}
}

void DTMFDecode::begin_analyse_test(vector<double> data)
{
	int i = 0;
	analyser = AudioAnalysis(10000, 8000, 10, 1024, 200, AudioAnalysis::None);
	while (!Buffer::getInstance()->checkFlag(0))
	{
		try
		{
			double value = data[i++];
			window.push_back(value);

			if (debug)
				debugData.push_back(value);

			if (window.size() == windowSize)
			{
				while (true)
				{
					try
					{

						add_analyseBuffer(window);
						break;
					}
					catch (...)
					{
						sf::sleep(sf::milliseconds(20));
					}
				}
				window.clear();
			}
		}
		catch (...)
		{
			sf::sleep(sf::milliseconds(20));

		}

		if (i == data.size())
		{
			testDone = true;
			break;
		}
	}
}

void DTMFDecode::stop()
{
	analyseStop = true;
}

vector<double> DTMFDecode::getDebugData()
{
	return debugData;
}

DTMFDecode::~DTMFDecode()
{
}

void DTMFDecode::add_analyseBuffer(vector<double> window)
{
	
	if (size >= 10)
		throw "wait";
	
	analyse[pointerInd] = async(launch::async, &AudioAnalysis::analysis,analyser, window);
	pointerInd = (pointerInd + 1) % 10;
	mutex_analyse.lock();
	size++;
	mutex_analyse.unlock();
}

unsigned short int DTMFDecode::take_analyseBuffer()
{
	if (size == 0)
		throw "wait";

	while (analyse[pointerOut].wait_for(chrono::milliseconds(1)) != future_status::ready)
	{
		if (Buffer::getInstance()->checkFlag(0))
			throw "wait";
	}
		
	unsigned short int returnValue = analyse[pointerOut].get();
	pointerOut = (pointerOut + 1) % 10;
	mutex_analyse.lock();
	size--;
	mutex_analyse.unlock();

	return returnValue;
}
