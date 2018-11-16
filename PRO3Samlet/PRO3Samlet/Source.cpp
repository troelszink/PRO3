
#include <thread>
#include <iostream>
#include "COSinitClient.h"
#include "OSInit.h"
#include "InitFysikLag.h"
#include "KOMinit.h"
#include "Buffer.h"


int main()
{
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


		KOMinit * initKOM = new KOMinit();
		kom = thread(&KOMinit::run, initKOM);

		InitFysikLag * fysik = new InitFysikLag();
		dsp = thread(&InitFysikLag::run, fysik);

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
	return 0;
}