#include "COSinitClient.h"



COSinitClient::COSinitClient()
{
}

void COSinitClient::run()
{
	ClientRequestReply * clientRequest = new ClientRequestReply();
	t1 = thread(&ClientRequestReply::upload, clientRequest, "Hello World", 1);
	t1.join();
}


COSinitClient::~COSinitClient()
{}
