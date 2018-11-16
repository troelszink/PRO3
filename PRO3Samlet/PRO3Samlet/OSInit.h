#include <thread>
#include "ServerRequestReply.h"


using namespace std;
class COSInit
{
public:
	COSInit();
	void run();
	~COSInit();

private:
	thread server;

};

