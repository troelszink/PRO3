#include "DTMFDecode.h"



DTMFDecode::DTMFDecode(int sizeWindow)
{
	windowSize = sizeWindow;
	debug = false;
}

DTMFDecode::DTMFDecode(int sizeWindow, bool Debug)
{
	windowSize = sizeWindow;
	debug = Debug;
}

void DTMFDecode::decode()
{
	analyser = AudioAnalysis(10000, 8000, 10, 1024, 4, 200,AudioAnalysis::None);

	while (!Buffer::getInstance()->checkFlag(0))
	{
		try
		{
			
			bufferEmpty = false;
			double value = Buffer::getInstance()->takeFromDTMF_SlicesBufferRecive();
			window.push_back(value);
			
			if (debug)
				debugData.push_back(value);

			if (window.size() == windowSize)
			{
				analyser.analysis(window);
				window.clear();
			}
		}
		catch(...){
			sf::sleep(sf::milliseconds(20));

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
