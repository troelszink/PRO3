#include "ServerRequestReply.h"



ServerRequestReply::ServerRequestReply()
{
	buffer = Buffer::getInstance();
}

void ServerRequestReply::extract_Execute()
{
	while (true && !Buffer::getInstance()->checkFlag(0))
	{
		try
		{
			for (int i = 0; i < buffer->getBufferLength(4); i++)
			{
				string elementS = buffer->getBufferElement(4, i);

				if (elementS[8] == '5')
				{
					string commandList = buffer->takeFrom_datalinkToApp();

					currentUser = commandList.substr(4, 4);

					addCommands(commandList);
					checkCommands(commandList);

					commands.erase(commands.begin());
				}
				while (!commands.empty())
				{
					if (commands[0][8] == '1') //write
					{
						string data = buffer->takeFrom_datalinkToApp();
						constructFile(fileNames[0], fileNames[0], 0, 0, data.substr(9, data.length() - 1));
						fileNames.erase(fileNames.begin());
						commands.erase(commands.begin());
					}

					else if (commands[0][8] == '2') //read
					{
						buffer->takeFrom_datalinkToApp();
						read(fileNames[0]);
						fileNames.erase(fileNames.begin());
						buffer->addTo_appToDatalink(currentUser + serverAddress + "2" + completeFile);
						commands.erase(commands.begin());
					}
					else if (commands[0][8] == '3') //remove
					{
						buffer->takeFrom_datalinkToApp();
						removeFile(fileNames[0]);
						fileNames.erase(fileNames.begin());
						commands.erase(commands.begin());
					}
				}

				if (elementS[8] == '0') //listFiles
				{
					buffer->addTo_appToDatalink(currentUser + serverAddress + "0" + sendFileList());
				}

				else if (elementS[8] == '4') //broadcast signal
				{
					//cout << requestBuffer[i].substr(0, 1) << endl;
				}
			}
		}
		
		catch (...)
		{
			this_thread::sleep_for(chrono::milliseconds(200));
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
