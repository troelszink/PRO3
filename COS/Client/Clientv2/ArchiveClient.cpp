#include "ArchiveClient.h"
#include <string>
#include <bitset>
#include <sstream>
#include <iostream>

using namespace std;
ArchiveClient::ArchiveClient()
{
	fileAmount = 0;
	characterAmount = 0;
	fileAmountInList = 0;
}

void ArchiveClient::constructFile(string name, string address, int root, int fileType, string dataToWrite)
{
	File newFile(name, address, root, fileType, dataToWrite);
	addFile(newFile);
	write(name, dataToWrite);
}


void ArchiveClient::addFile(File &f)
{																				// For hvert fil tilf�jet til vektoren Files, incrementeres fileAmount.
	files.push_back(&f);
	fileAmount++;
}

void ArchiveClient::listFiles()
{
	for (int i = 0; i < fileAmount; i++)
	{
		cout << files[i]->getAddress() + files[i]->getFileType() << endl;
	}
}

string ArchiveClient::searchForFileAddress(string fileName)
{
	string fileAddress;															// Filens addresse i selve server-mappen.
	string fileRootAddress;														// Root-adressen til selve serveren.
	string fileExtension;														// Filens type.
	
	for (int i = 0; i < fileAmount; i++)										// For-loopet k�rer for alle filer i vektoren Files, 																			// hvorefter der tjekkes p� om en af dem matcher navnet p� den �nskede fil.
	{
		if (files[i]->getName() == fileName)									// Der tjekkes hvorvidt fil i's navn er det samme som den �nskede fils navn.
		{
			fileAddress = files[i]->getAddress();								
			fileRootAddress = getRootAddress();
			fileExtension = getFileType();
			return fileRootAddress+fileAddress+fileExtension;					// Returnerer den fulde sti til filen.
		}
	}
}



void ArchiveClient::write(string fileName, string receivedFile)			// Downloader den �nskede fil og konverterer den til en ASCII-string
{
	ofstream fileToWrite;														// Opretter en stream, hvori en fil kan �bnes.

	//void getDataFromFile(); // Kalder p� KOM-delen til at hente data fra en �nsket fil med navn: fileName

	// hvis data modtaget, gem i dataToWrite.

	fileToWrite.open(fileName.append(".txt"));									// Den �nskede fil �bnes.
	fileToWrite << receivedFile;												// Det �nskede data skrives ind i den �bne fil.
	fileToWrite.close();

	cout << receivedFile << endl;

	receivedFile.clear();														// Indholdet p� receivedFile slettes, s� det tidligere indhold ikke kommer med de nye filer
}


void ArchiveClient::read(string specificFile)
{
	ifstream openFile(searchForFileAddress(specificFile));										// �bner en bestemt fil, specificFile, ind i streamen. 
	string readFile{ istreambuf_iterator<char>(openFile), istreambuf_iterator<char>() };		// Opretter en constructor for en string, hvor hvert char element fra filen appendes til stringen.
	completeFile = readFile;																	// S�tter completeFile lig readFile, hvilket er den l�ste fil.												// Skal fjernes - kun til test.
}



string ArchiveClient::getCompleteFile()
{
	return completeFile;
}

void ArchiveClient::removeFile(string fileName)
{
	/*string fileToBeRemoved = searchForFileAddress(fileName);

	const char *fileToBeRemovedConv = fileToBeRemoved.c_str();

	remove(fileToBeRemovedConv);*/

	// Lav en kommando, der fort�ller serveren, at den skal slette en fil
}

ArchiveClient::~ArchiveClient()
{}
