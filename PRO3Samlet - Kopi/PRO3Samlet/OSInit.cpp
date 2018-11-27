#include "OSInit.h"



COSInit::COSInit()
{}

void COSInit::run()
{
	ServerRequestReply * SRR = new ServerRequestReply();
	server = thread(&ServerRequestReply::extract_Execute, SRR);

	server.join();
}


COSInit::~COSInit()
{
}
