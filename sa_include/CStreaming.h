#ifndef __CSTREAMING_H__
#define __CSTREAMING_H__

class CStreaming
{
public:
	static int RequestModel(int, int);
	static int RequestSpecialModel(int, const char*, int);
	static int LoadAllRequestedModels(bool);
};

#endif