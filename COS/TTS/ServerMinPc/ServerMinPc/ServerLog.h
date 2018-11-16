#include <vector>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

class ServerLog
{
public:

	ServerLog();

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	void    logListFiles();

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	void	logWrite(int fileOnList, string fileName);			//N�r en fil tilf�jes serveren logger den filens nummer p� listen af filer.
	void	logRead(int fileOnList, string fileName);			//N�r en fil hentes fra serveren logger den filens nummer p� listen af filer.
	void	logRemove(int fileOnList, string fileName);			//N�r en fil fjernes fra serveren logger den filens nummer p� listen af filer.
	void	logLogin(int userId);
	void	logLogout(int userId);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	void	addLogElement(string toBeLoged);					//Tilf�jer et element til vektoren logVector.

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	void	logSaveToFile();									//Gemmer logen til en fil p� serveren.
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	string	logChanges(string ClientId);

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

	~ServerLog();

protected:

	int logAmount;
	vector <string> logVector;
};

