#include "PlayDTMF.h"


PlayDTMF::PlayDTMF()
{
	
}

void PlayDTMF::handler()
{
	string message = "";
	while (true)
	{
		try
		{
			bitset<4> tone = Buffer::getInstance()->takeFrom_datalinkToSound();
			message += bit2hex(tone);
		}
		catch (...)
		{
			if (Buffer::getInstance()->checkFlag(2) && Buffer::getInstance()->checkFlag(3))
			{
				Buffer::getInstance()->setFlag(3, false);
				play2(message);
				message.clear();
				Buffer::getInstance()->setFlag(2, false);
				Buffer::getInstance()->setFlag(1, false);
			}
				
		}

		if (Buffer::getInstance()->checkFlag(0))
			break;
	}
}

char PlayDTMF::bit2hex(bitset<4> bit)
{
	if (bit == 0)
		return '0';
	else if (bit == 1)
		return '1';
	else if (bit == 2)
		return '2';
	else if (bit == 3)
		return '3';
	else if (bit == 4)
		return '4';
	else if (bit == 5)
		return '5';
	else if (bit == 6)
		return '6';
	else if (bit == 7)
		return '7';
	else if (bit == 8)
		return '8';
	else if (bit == 9)
		return '9';
	else if (bit == 10)
		return 'A';
	else if (bit == 11)
		return 'B';
	else if (bit == 12)
		return 'C';
	else if (bit == 13)
		return 'D';
	else if (bit == 14)
		return 'E';
	else if (bit == 15)
		return 'F';
}




void PlayDTMF::play2(std::string aString)
{
	durationPlay = 100;//sætter tiden i ms
	unsigned numbersOfWindows = 5;//Hvor mange vinduer, hver tone, skal opdeles i
	unsigned durationPause = durationPlay;// / numbersOfWindows;
	inString = aString;
	for (int i = 0; i < inString.length(); i++)
	{
		char oneChar = inString[i];
		//inString[i] = oneChar;
		switch (oneChar)
		{
		case '0': case '1': case '2': case '3': freqs[0] = 697; break;
		case '4': case '5': case '6': case '7': freqs[0] = 770; break;
		case '8': case '9': case 'A': case 'B': freqs[0] = 852; break;
		case 'C': case 'D': case 'E': case 'F': freqs[0] = 941; break;
		}
		switch (oneChar)
		{
		case '0': case '4': case '8': case 'C': freqs[1] = 1209; break;
		case '1': case '5': case '9': case 'D': freqs[1] = 1336; break;
		case '2': case '6': case 'A': case 'E': freqs[1] = 1477; break;
		case '3': case '7': case 'B': case 'F': freqs[1] = 1633; break;
		}
		raw = new sf::Int16[sampleRate];
		buffer = new sf::SoundBuffer;
		sound = new sf::Sound;
		genBuffer();
		play();
		sf::sleep(sf::milliseconds(durationPause));
	}
}



	PlayDTMF::~PlayDTMF()
	{

	}

void PlayDTMF::genBuffer()
{
	
	const double TWO_PI = 6.28318;
	double f1inc = freqs[0] / sampleRate;
	double f2inc = freqs[1] / sampleRate;
	unsigned i;
	double f1 = 0;
	double f2 = 0;
	for (i = 0; i<sampleRate; i++)
	{
		raw[i] = amp * (sin(f1 * TWO_PI) + sin(f2 * TWO_PI));
		f1 += f1inc; f2 += f2inc;
	}
	if (!buffer->loadFromSamples(raw, sampleRate, 1, sampleRate))
	{
		std::cerr << "Error loading buffer" << std::endl;
		return;
	}
	sound->setBuffer(*buffer);
	sound->setLoop(true);
}

void PlayDTMF::play()
{
	sound->play();
	sf::sleep(sf::milliseconds(durationPlay));
	sound->stop();
}




