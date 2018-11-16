#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
#include <deque>
#include <mutex>

#include "AudioSample.h"
#include "Buffer.h"

using namespace sf;
using namespace std;
class StreamRecorder : public sf::SoundRecorder
{
public:
	StreamRecorder();
	void startStreamRecorder(int aRecTime);//(int aRecTime, Buffer & buf);
	virtual bool onStart();
	virtual bool onProcessSamples(const Int16* samples, size_t sampleCount);// onProcessSample er en indbygget SFML metode, som kan streame en bid real time. længden af denne bid indstilles med onStart metoden ovenover
	//virtual void onStop();
	~StreamRecorder();
	
private:
	vector<vector<int>>DTMF_SlicesBufferRecive;//Er til at opbevare bider af funde og endnu ikke godkendte DTMF toner.

};

