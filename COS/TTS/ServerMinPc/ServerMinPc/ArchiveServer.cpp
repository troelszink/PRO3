#include "ArchiveServer.h"
#include <string>
#include <bitset>
#include <stdio.h>

using namespace std;
ArchiveServer::ArchiveServer()
{
	fileAmount = 0;
	fileNameAmount = 0;
	characterAmount = 0;
	currentFile = 0;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

void ArchiveServer::constructFile(string name, string address, int root, int fileType, string dataToWrite)
{

	File newFile(name, address, root, fileType, dataToWrite);
	addFile(newFile);
	write(name, dataToWrite);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

string ArchiveServer::searchForFileAddress(string fileName)
{
	string fileAddress;															// Filens addresse i selve server-mappen.
	string fileRootAddress;														// Root-adressen til selve serveren.
	string fileExtension;														// Filens type.

	for (int i = 0; i < fileAmount; i++)										// For-loopet k�rer for alle filer i vektoren Files, 
																				// hvorefter der tjekkes p� om en af dem matcher navnet p� den �nskede fil.
	{

		if (files[i].getName() == fileName)									// Der tjekkes hvorvidt fil i's navn er det samme som den �nskede fils navn.
		{
			fileAddress = files[i].getAddress();
			fileRootAddress = getRootAddress();
			fileExtension = getFileType();
			string fileRAE = fileRootAddress.append(fileAddress).append(fileExtension);
			return fileRAE;														// Returnerer den fulde sti til filen.
		}

	}
}

void ArchiveServer::addFile(File f)
{																				// For hvert fil tilf�jet til vektoren Files, incrementeres fileAmount.
	files.push_back(f);
	fileAmount++;
}

void ArchiveServer::addFileNames(string n)
{
	fileNames.push_back(n);
	fileNameAmount++;
}

void ArchiveServer::listFiles()
{
	cout << endl << "-----------------------------[Files on server]----------------------------------" << endl;
	for (int i = 0; i < fileAmount; i++)
	{
		cout << "~[ " <<files[i].getAddress() + files[i].getFileType() << " ]~" << endl;
	}
	cout << endl;
}

void ArchiveServer::fileOnServer(string fileNameCon)
{

	for (int i = 0; i < fileAmount; i++)										// For-loopet k�rer for alle filer i vektoren Files, 
																				// hvorefter der tjekkes p� om en af dem matcher navnet p� den �nskede fil.
	{

		if (files[i].getName() == fileNameCon)									// Der tjekkes hvorvidt fil i's navn er det samme som den �nskede fils navn.
		{
			currentFile = i;
		}

	}
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------//


void ArchiveServer::write(string fileName, string dataToWrite)
{
	string testString = fileName;
	ofstream fileToWrite;														// Opretter en stream, hvori en fil kan �bnes.
	fileToWrite.open(fileName.append(".txt"));									// Den �nskede fil �bnes.
	fileToWrite << dataToWrite;													// Det �nskede data skrives ind i den �bne fil.
	fileToWrite.close();
	fileOnServer(testString);
	logWrite(currentFile,testString);														// Logger p� serveren hvilken fil der er uploadet, og af hvilken klient.
	cout << endl << "-------------------------[File written to server]------------------------------" << endl << endl;
	cout << "~[ " << fileName << ".txt ]~"<< endl;
}

void ArchiveServer::read(string specificFile)
{
	ifstream openFile(searchForFileAddress(specificFile));										// �bner en bestemt fil, specificFile, ind i streamen. 
	string readFile{ istreambuf_iterator<char>(openFile), istreambuf_iterator<char>() };		// Opretter en constructor for en string, hvor hvert char element fra filen appendes til stringen.
	completeFile = readFile;																	// S�tter completeFile lig readFile, hvilket er den l�ste fil.
	cout << endl << "--------------------------[File read from server]------------------------------" << endl << endl << "~[ " <<specificFile << ".txt ]~" << endl;
	cout <<endl<< specificFile << " contains:" << endl << completeFile << endl;																// Skal fjernes - kun til test.
	fileOnServer(specificFile);
	logRead(currentFile, specificFile);																	// Logger p� serveren hvilken fil der er downloadet, og af hvilken klient.
}

void ArchiveServer::removeFile(string fileName)
{

	string fileToBeRemoved = searchForFileAddress(fileName);

	const char *fileToBeRemovedConv = fileToBeRemoved.c_str();

	remove(fileToBeRemovedConv);
	fileOnServer(fileName);
	logRemove(currentFile, fileName);																		//Logger p� serveren hvilken fil der er slettet, og af hvilken klient.
	fileOnServer(fileName);
	files.erase(files.begin() + currentFile);
	fileAmount = fileAmount - 1;
	cout << endl << "-------------------------[File removed from server]-----------------------------" << endl;
	cout << "~[ "<< fileName << ".txt ]~"<< endl;
}


//-----------------------------------------------------------------------------------------------------------------------------------------------------------//



string ArchiveServer::getCompleteFile()
{
	return completeFile;
}

int ArchiveServer::getFileAmount()
{
	return fileAmount;
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

void ArchiveServer::checkCommands(string commandList)
{

	int length=0;
	int lineAmount = 0;
	int nameLength;
	int fileNumberLength=0;

	login(commandList.substr(4,4));

	commandList.erase(0, commandList.find('\n'));

	commandList.push_back('\n');
	int lastPos = commandList.length() - 1;
	while (lastPos >= 0)
	{
		if (commandList[lastPos] == 10)
		{
			lineAmount++;
		}
		lastPos--;
	}

	for (int i = 0; i < lineAmount; i++)
	{
		if (48 < (int)commandList[5] < 58)
		{
			int i = 5;
			while (commandList[i]!=32)
			{
				fileNumberLength++;
			}
			while ((int)commandList[length] != 10)
			{
				length++;
			}
			addFileNames(files[stoi(commandList.substr(5, fileNumberLength))].getName());
			commandList.erase(0,length);
			length = 0;

		}

		else
		{
			for (int i = 0; i < lineAmount; i++)
			{
				while ((int)commandList[length] != 10)
				{
					length++;
				}
				nameLength = length - 5;
				addFileNames(commandList.substr(length - nameLength, nameLength));
				commandList.erase(0, length);
				length = 0;
			}
		}
	}
}

ArchiveServer::~ArchiveServer()
{
}
