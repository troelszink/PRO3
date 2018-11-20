#include "COSinitClient.h"



COSinitClient::COSinitClient()
{
}

void COSinitClient::run()
{
	ClientRequestReply * clientRequest = new ClientRequestReply();
	clientRequest->constructFile("Hello World", "Hello World", 1, 1, "00011111Hej");
	clientRequest->upload("Hello World", 1);
	t1 = thread(&ClientRequestReply::upload, clientRequest, "Hello World", 1);
	t1.join();
}


COSinitClient::~COSinitClient()
{}
