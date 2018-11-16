#include "recordDTMF.h"
#include <iostream>
#include<ctime>
using namespace std;
using namespace sf;


void recordDTMF::record(int aRecTime)//(int aRecTime, bool print = false)
{
	int sampleRate = 8000; //Angiver sampleraten
	sf::SoundBufferRecorder recorderBuffer;

	cout << "Recording started and running for: " << aRecTime << " seconds" << endl;
	recorderBuffer.start(sampleRate);
	sf::sleep(sf::seconds(aRecTime));

	recorderBuffer.stop();
	cout << "Recording finished" << endl;

	const sf::SoundBuffer& bufferOut = recorderBuffer.getBuffer();

	const sf::Int16* samples = bufferOut.getSamples();
	int count = bufferOut.getSampleCount();


	vector<Int16>SampleVector;
	for (int i = 0; i < count; i++)
	{
		Int16 aSample = samples[i];
		SampleVector.push_back(aSample);
	}

	time_t varTime = time(0);
		string fileName = "SF" + to_string(sampleRate) + "signal"+ to_string(varTime)+".txt";
		ofstream outFile(fileName);
		for (const auto &e : SampleVector) outFile << e << "\n";

		cout << "Recording saved as: " << fileName << endl;

		outFile.close();
	
}

recordDTMF::recordDTMF()
{
}

recordDTMF::~recordDTMF()
{
}
