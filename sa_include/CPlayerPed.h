#ifndef __CPLAYERPED_H__
#define __CPLAYERPED_H__

#include "CPed.h"

class CPlayerPed : public CPed
{
private:
	int reverse_me;
	
public:
	CPlayerPed();
	virtual ~CPlayerPed();
	
	void SetWantedLevel(int a2);
};

#endif