#include "InitFysikLag.h"



InitFysikLag::InitFysikLag()
{}

void InitFysikLag::run()
{
	
	DTMFDecode * dtmfdecode = new DTMFDecode(160, false);
	decode = thread(&DTMFDecode::decode, dtmfdecode);

	StreamRecorder * streamrecorder = new StreamRecorder();
	record = thread(&StreamRecorder::startStreamRecorder, streamrecorder, 60);

	PlayDTMF * playDTMF = new PlayDTMF();
	send = thread(&PlayDTMF::handler, playDTMF);
	
	decode.join();
	record.join();
	send.join();
}


InitFysikLag::~InitFysikLag()
{}
