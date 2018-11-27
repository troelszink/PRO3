#include "InitFysikLag.h"



InitFysikLag::InitFysikLag()
{}

void InitFysikLag::run()
{
	
	DTMFDecode * dtmfdecode = new DTMFDecode(160, 4, false);
	decode = thread(&DTMFDecode::begin_analyse,dtmfdecode);
	decode2 = thread(&DTMFDecode::decode, dtmfdecode);

	StreamRecorder * streamrecorder = new StreamRecorder();
	record = thread(&StreamRecorder::startStreamRecorder, streamrecorder, 60);

	PlayDTMF * playDTMF = new PlayDTMF();
	send = thread(&PlayDTMF::handler, playDTMF);
	
	decode.join();
	decode2.join();
	record.join();
	send.join();
}


InitFysikLag::~InitFysikLag()
{}
