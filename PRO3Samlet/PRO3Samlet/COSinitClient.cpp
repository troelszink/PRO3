#include "COSinitClient.h"



COSinitClient::COSinitClient()
{
}

void COSinitClient::run()
{
	ClientRequestReply * clientRequest = new ClientRequestReply();
	clientRequest->constructFile("Commands", "Commands", 1, 1, "000011115\n000011111Hello World Beast");
	clientRequest->constructFile("Hello World Beast", "Hello World Beast", 1, 1, "000011111mmm (.)(.)");
	t1 = thread(&ClientRequestReply::upload, clientRequest, "Commands", 1);
	t2 = thread(&ClientRequestReply::upload, clientRequest, "Hello World Beast", 1);
	t1.join();
	t2.join();
}


COSinitClient::~COSinitClient()
{}
