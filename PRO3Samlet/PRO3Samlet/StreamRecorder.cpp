#include "StreamRecorder.h"
#include "DTMFDecode.h"



StreamRecorder::StreamRecorder()
{
}


void StreamRecorder::startStreamRecorder(int aRecTime)//P7B(int aRecTime, Buffer & buf)
{
	//buffer = &buf;
	while (true)
	{
		if (StreamRecorder::isAvailable() && !Buffer::getInstance()->checkFlag(1))
		{
			StreamRecorder micInput;
			int sampleRate = 8000;
			//cout << "Recording started and running for: " << aRecTime << " seconds" << endl;
			micInput.start(sampleRate);
			//std::this_thread::sleep_for(std::chrono::seconds(aRecTime));//Alternativ timer
			while (true)
			{
				sf::sleep(sf::milliseconds(120));

				if (Buffer::getInstance()->checkFlag(1) || Buffer::getInstance()->checkFlag(0))
					break;
			}

			micInput.stop();
			//cout << "recording finnished" << endl;
		}
		else 
			sf::sleep(sf::milliseconds(50)); 

		if (Buffer::getInstance()->checkFlag(0))
			break;
	}
	
}

bool StreamRecorder::onStart()
{
	sf::SoundRecorder::setProcessingInterval(sf::milliseconds(20));// Sætter længden af vindues størelsen i onProcessSamples.
	return true;
}

bool StreamRecorder::onProcessSamples(const Int16 * samples, size_t sampleCount)//Tager et vindue ad gangen.
{

	//cout << "Number of samples: " << sampleCount << endl;

	//int maxSample = 2;
	//for (int i = 0; i < sampleCount; i++)
	//{
	//	if (abs(samples[i]) > maxSample)
	//		maxSample = abs(samples[i]);
	//}
	//cout << "Max: " << maxSample << '\n' << endl;

	for (int i = 0; i < sampleCount; i++)
		Buffer::getInstance()->addToDTMF_SlicesBufferRecive((int) samples[i]);
	
	return true;
}



StreamRecorder::~StreamRecorder()
{
}
