
#include <thread>
#include <iostream>
#include "COSinitClient.h"
#include "OSInit.h"
#include "InitFysikLag.h"
#include "KOMinit.h"
#include "Buffer.h"

void DeviceSettings()//P2A
{
	if (SoundRecorder::isAvailable())
	{

		vector<string> deviceNameList = SoundRecorder::getAvailableDevices();
		cout << "This is the list of your " << deviceNameList.size() << " available devices: " << endl;
		for (int i = 0; i < deviceNameList.size(); i++)
		{
			cout << i << ": " << deviceNameList[i] << endl;

		}

		cout << endl << "Current device is: " << SoundRecorder::getDefaultDevice() << endl;
	}
	else
		cout << "There are no devices available" << endl; // simplel fejlmeddelelse
		//throw "There are no devices available";// knap så simplel


}

int main()
{
	DeviceSettings();
	thread cos;
	thread kom;
	thread dsp;
	cout << "Work as client (1) or server (0) or break(-1)" << endl;
	int a; cin >> a;

	if (a != -1)
	{

		if (a == 1)
		{
			COSinitClient * client = new COSinitClient();
			cos = thread(&COSinitClient::run, client);
		}
		else
		{
			COSInit * server = new COSInit();
			cos = thread(&COSInit::run, server);
		}

		InitFysikLag * fysik = new InitFysikLag();
		dsp = thread(&InitFysikLag::run, fysik);

		KOMinit * initKOM = new KOMinit();
		kom = thread(&KOMinit::run, initKOM);


		a = 0;
		cout << "enter 1 to stop" << endl;
		while (a != 1)
		{
			cin >> a;
		}

		Buffer::getInstance()->setFlag(0, true);

		dsp.join();
		kom.join();
		cos.join();

	}
	system("pause");
	return 0;
}