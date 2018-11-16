#include <vector>
#include "File.h"
#include <fstream>
#include <iostream>

using namespace std;
class ArchiveClient : public File
{
public:

	ArchiveClient();
	
	void constructFile(string name, string address, int root, int fileType, string dataToWrite);

	void addFile(File&);								// Tilf�jer filer til vektoren Files. Her ligger alle filer p� serveren.
	void listFiles();									// For os selv lige pt s� vi kan se hvilke filer der er i mappen.

	string searchForFileAddress(string fileName);		// Leder efter adressen p� filen med oplyste navn. Hvis filen findes returneres dens fulde adresse.
	
	void write(string fileName, string receivedFile);						// Opretter en fil, i f�rste omgang .txt, hvilken der skrives det �nskede indhold til.
	void read(string specificFile);						// �bner en fil og l�ser den ind i en stream, hvorefter indholdet gemmes i en string kaldet completeFile.

	string getCompleteFile();			//KIIIG			// KUN TIL TEST

	void removeFile(string fileName);

	~ArchiveClient();

protected:

	vector <File*> files;
	string completeFile;
	string receivedFile = "";

	int fileAmount;
	int characterAmount;
	int fileAmountInList;

};

