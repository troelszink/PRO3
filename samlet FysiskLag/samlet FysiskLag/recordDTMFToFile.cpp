#include "recordDTMFToFile.h"



recordDTMFToFile::recordDTMFToFile(int aTime) //Optager og gemmer som lydfil.
{
	
	int sampleRate = 8000; //Angiver sampleraten

	SoundBufferRecorder recorderBuffer;// Opretter en buffer ved navn recorderBuffer
	cout << " " << endl;

	cout << "Recording started and running for: " << aTime << " seconds" << endl;
	recorderBuffer.start(sampleRate);// Starter optagelse til bufferen med angivede samplerate
	sf::sleep(sf::seconds(aTime));//Venter i aTime sekunder

	recorderBuffer.stop(); //Stopper optagele igen
	cout << "Recording ended" << endl;


	
	const SoundBuffer& bufferOut = recorderBuffer.getBuffer();//Henter recorderBuffer ind i en ny buffer kaldet bufferOut, som er konstant og derfor kan gemmes
	string aRecName = "recording.ogg";
	bufferOut.saveToFile(aRecName);//gemmer bufferIn til filen aRecName
	cout << "Recording saved as: " << aRecName << endl;
}


/*
void recordDTMFToFile::PlayFromFile(string aFileName)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(aFileName))
	{
		std::cout << "Error while loading music" << std::endl;
		sf::sleep(sf::seconds(5));
	
	}
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	*/
	/*
	sf::SoundBuffer Buffer;
	Buffer.LoadFromFile("sound.wav");
	
	const SoundBufferRecorder& bufferINConst = bufferIN.getBuffer()
	
	bufferOut.saveToFile(aFileName);//gemmer bufferIn til filen aRecName
	
}
*/
// mangler metode til at hente en optagelse ind fra fil P5B

recordDTMFToFile::~recordDTMFToFile()
{
}
