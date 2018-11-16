#include "ServerRequestReply.h"



ServerRequestReply::ServerRequestReply()
{
	buffer = Buffer::getInstance();
}

void ServerRequestReply::extract_Execute()
{
	while (!buffer->getBufferLength(4)==0)
	{
		for (int i = 0; i < buffer-> getBufferLength(4); i++)
		{
			string elementS = buffer-> getBufferElement(4, i);

			if (elementS[8] == '5')
			{
				string commandList = buffer->takeFrom_datalinkToApp();
				
				currentUser = commandList.substr(4, 4);

				addCommands(commandList);
				checkCommands(commandList);

				commands.erase(commands.begin());

				int currentCommand=0;
				while (!commands.empty())
				{

				if (commands[currentCommand][8]=='1') //write
					{
					string data = buffer->takeFrom_datalinkToApp();
						constructFile(fileNames[0], fileNames[0], 0, 0, data.substr(9,data.length()-1));
						fileNames.erase(fileNames.begin());
						commands.erase(commands.begin());
					}

				else if (commands[currentCommand][8] == '2') //read
					{
						buffer->takeFrom_datalinkToApp();
						read(fileNames[0]);
						fileNames.erase(fileNames.begin());
						buffer->addTo_appToDatalink(currentUser+serverAddress+"2"+completeFile);
						commands.erase(commands.begin());
					}
				else if (commands[currentCommand][8] == '3') //remove
					{
						buffer->takeFrom_datalinkToApp();
						removeFile(fileNames[0]);
						fileNames.erase(fileNames.begin());
						commands.erase(commands.begin());
					}
				}
			}

			else if (elementS[8] == '0') //listFiles
			{
				listFiles();
			}
			else if (elementS[8] == '4') //broadcast signal
			{
				//cout << requestBuffer[i].substr(0, 1) << endl;
			}
		

		}

	}
}

void ServerRequestReply::addCommands(string receivedCommands)
{
	int lineAmount = 0;
	int lastPos = receivedCommands.length() - 1;
	string tmp;
	while (lastPos >= 0)
	{
		if (receivedCommands[lastPos] == 10)
		{
			lineAmount++;
		}
		lastPos--;
	}
	for (int i = 0; i < lineAmount; i++)
	{
		tmp = receivedCommands.substr(0, receivedCommands.find('\n'));
		commands.push_back(tmp);
		receivedCommands.erase(0, receivedCommands.find('\n'));
	}
}




ServerRequestReply::~ServerRequestReply()
{
}
