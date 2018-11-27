#include "AudioAnalysis.h"



AudioAnalysis::AudioAnalysis()
{}

AudioAnalysis::AudioAnalysis(int thres, int sampleRate, int hexthreshold, int Padding,int ampThres, filterActive factive)
{

	amplitudeThreshold = ampThres;
	thresholdForTone = thres;
	samplerate = sampleRate;
	hexThreshold = hexthreshold;
	padding = Padding;
	active = factive;

	// Til test
	mValues = {18, 19, 20, 21, 22, 23, 25, 26, 31, 32, 35, 36, 38, 39, 42, 43};
	freqValues = {697, 697, 770, 770, 852, 852, 941, 941, 1209, 1209, 1336, 1336, 1477, 1477, 1633, 1633};
}
// Rigtige analyse
unsigned short int AudioAnalysis::analysis(vector<double> signal)
{

	if (mean(signal))
	{
		vector<double> filterSignal = filter(signal);
		filterSignal = removeBelow(filterSignal);
		return findTones(filterSignal);
	}
	else
	{
		return 16;
	}
}


void AudioAnalysis::sendTone(unsigned short int index)
{
	//tones.push_back(index);
}

unsigned short int AudioAnalysis::findTones(vector<double> splitSignal)
{
	vector<int> freqs;
	try
	{
		freqs = frequencyInSignal(DSPMath().toComplex(splitSignal));
	}
	catch(string s)
	{
		return 16;
	}
	

	if (freqs[0] == 697 && freqs[1] == 1209)
		return 0;
	else if (freqs[0] == 697 && freqs[1] == 1336)
		return 1;
	else if (freqs[0] == 697 && freqs[1] == 1477)
		return 2;
	else if (freqs[0] == 697 && freqs[1] == 1633)
		return 3;
	else if (freqs[0] == 770 && freqs[1] == 1209)
		return 4;
	else if (freqs[0] == 770 && freqs[1] == 1336)
		return 5;
	else if (freqs[0] == 770 && freqs[1] == 1477)
		return 6;
	else if (freqs[0] == 770 && freqs[1] == 1633)
		return 7;
	else if (freqs[0] == 852 && freqs[1] == 1209)
		return 8;
	else if (freqs[0] == 852 && freqs[1] == 1336)
		return 9;
	else if (freqs[0] == 852 && freqs[1] == 1477)
		return 10;
	else if (freqs[0] == 852 && freqs[1] == 1633)
		return 11;
	else if (freqs[0] == 941 && freqs[1] == 1209)
		return 12;
	else if (freqs[0] == 941 && freqs[1] == 1336)
		return 13;
	else if (freqs[0] == 941 && freqs[1] == 1477)
		return 14;
	else if (freqs[0] == 941 && freqs[1] == 1633)
		return 15;

	return 16;
}


vector<double> AudioAnalysis::filter(vector<double> signal)
{
	vector<double> data;
	switch (active)
	{
		case AudioAnalysis::None:
			return signal;
			break;
		case AudioAnalysis::Basic:
			for (int i = 0; i < signal.size(); i++)
			{
				data.push_back(filters[0].filter(signal[i]));
			}
			return data;
			break;
		case AudioAnalysis::Advancdes:
			break;
	}
	return signal;
}

vector<int> AudioAnalysis::frequencyInSignal(vector<complex<double>> signal)
{
	vector<complex<double>> padSignal = DSPMath().zeroPadding(signal, padding);
	vector< complex<double> > freqSignal = DSPMath().fft(padSignal);

	vector<double> ampl = DSPMath().amplitude(freqSignal);
	

	vector<double> freq = DSPMath().linspace(0, samplerate, freqSignal.size());

	vector<unsigned int> index = DSPMath().find(ampl, thresholdForTone, DSPMath::ABOVE);

	vector<int> freqSelect;
	double lowFreq = 0;
	double lowMax = 0;
	double highFreq = 0;
	double highMax = 0;
	for (int i = 0; i < index.size(); i++)
	{
		
		if (500 < freq[index[i]]  && freq[index[i]] < 1000)
		{
			
			if ((697 - hexThreshold) < freq[index[i]] && freq[index[i]] < (697 + hexThreshold))
			{
				if (lowMax < ampl[index[i]])
				{
					lowMax = ampl[index[i]];
					lowFreq = 697;
				}
			}
			else if ((770 - hexThreshold) < freq[index[i]] && freq[index[i]] < (770 + hexThreshold))
			{
				if (lowMax < ampl[index[i]])
				{
					lowMax = ampl[index[i]];
					lowFreq = 770;
				}
			}
			else if ((852 - hexThreshold) < freq[index[i]] && freq[index[i]] < (852 + hexThreshold))
			{
				if (lowMax < ampl[index[i]])
				{
					lowMax = ampl[index[i]];
					lowFreq = 852;
				}
			}
			else if ((941 - hexThreshold) < freq[index[i]] && freq[index[i]] < (941 + hexThreshold))
			{
				if (lowMax < ampl[index[i]])
				{
					lowMax = ampl[index[i]];
					lowFreq = 941;
				}
			}
		}
		else if (1000 < freq[index[i]] && freq[index[i]] < 1700)
		{
			
			if ((1209 - hexThreshold) < freq[index[i]] && freq[index[i]] < (1209 + hexThreshold))
			{
				if (highMax < ampl[index[i]])
				{
					highMax = ampl[index[i]];
					highFreq = 1209;
				}
			}
			else if ((1336 - hexThreshold) < freq[index[i]] && freq[index[i]] < (1336 + hexThreshold))
			{
				if (highMax < ampl[index[i]])
				{
					highMax = ampl[index[i]];
					highFreq = 1336;
				}
			}
			else if ((1477 - hexThreshold) < freq[index[i]] && freq[index[i]] < (1477 + hexThreshold))
			{
				if (highMax < ampl[index[i]])
				{
					highMax = ampl[index[i]];
					highFreq = 1477;
				}
			}
			else if ((1633 - hexThreshold) < freq[index[i]] && freq[index[i]] < (1633 + hexThreshold))
			{
				if (highMax < ampl[index[i]])
				{
					highMax = ampl[index[i]];
					highFreq = 1633;
				}
			}
		}
	}

	freqSelect.push_back(lowFreq);
	freqSelect.push_back(highFreq);

	if (freqSelect.size() == 0)
		throw "Empty";

	return freqSelect;
}

bool AudioAnalysis::mean(vector<double> signal)
{
	double total = 0;
	for (int i = 0; i < signal.size(); i++)
		total += abs(signal[i]);
	//cout << total / signal.size() << endl;
	if (total / signal.size() < amplitudeThreshold)
		return false;

	return true;

}

vector<double> AudioAnalysis::removeBelow(vector<double> signal)
{
	for (int i = 0; i < signal.size(); i++)
	{
		if (abs(signal[i]) < 200)
			signal[i] = 0;

	}
	return signal;

}
// Genbrugt funktioner
vector<int> AudioAnalysis::getTones()
{
	return tones;
}

void AudioAnalysis::setFilter(filterActive fActive)
{
	active = fActive;
}

AudioAnalysis::~AudioAnalysis()
{}

void AudioAnalysis::setup()
{
	switch (active)
	{
		case AudioAnalysis::None:
			break;
		case AudioAnalysis::Basic:
			break;
		case AudioAnalysis::Advancdes:
			break;
	}
}

void AudioAnalysis::read(string fil)
{
	ifstream file("Settings/" + fil);

	if (file.is_open())
	{
		string line;
		bool kasade = false;
		bool parelle = false;
		int lineNr = 0;
		vector<double> a;
		vector<double> b;
		vector<BasicFilter> filt;
		vector<KaskadeFilter> kasFilter;

		while (getline(file, line))
		{
			if (line.compare("p") == 0)
			{
				if (parelle)
				{
					if (kasade)
					{
						kasFilter.push_back(KaskadeFilter(filt));
						filt.clear();
					}

					if (kasFilter.size() != 0)
					{
						filters.push_back(ParelleFilter(kasFilter));
						kasFilter.clear();
					}
					else if (filt.size() != 0)
					{
						filters.push_back(ParelleFilter(filt));
						filt.clear();
					}
				}
				else
					parelle = true;
				

			}
			else if (line.compare("k") == 0)
			{
				if (kasade)
				{
					kasFilter.push_back(KaskadeFilter(filt));
					filt.clear();
				}
				kasade = true;
				lineNr = 0;
			}
			else if (line.compare("d") == 0)
			{
				kasade = false;
				lineNr = 0;
			}
			else
			{

				string letter;
				for (int i = 0; i < line.length(); i++)
				{
					if (line[i] == ' ')
					{
						if (lineNr == 0)
							a.push_back(stod(letter));
						else
							b.push_back(stod(letter));

						letter.clear();
					}
					else
						letter += line[i];
				}

				if (lineNr == 1)
				{
					filt.push_back(BasicFilter(a, b));
					a.clear();
					b.clear();
					lineNr = 0;
				}
				else
					lineNr++;

			}
		}

		if (kasade)
		{
			kasFilter.push_back(KaskadeFilter(filt));
			filt.clear();
		}

		if (kasFilter.size() != 0)
		{
			filters.push_back(ParelleFilter(kasFilter));
			kasFilter.clear();
		}
		else if (filt.size() != 0)
		{
			filters.push_back(ParelleFilter(filt));
			filt.clear();
		}

	}
	file.close();




}


