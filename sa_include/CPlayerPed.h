#ifndef __CPLAYERPED_H__
#define __CPLAYERPED_H__

#include "CPed.h"

class CPlayerPed : public CPed
{
private:
	char reverse_me[8];
	
public:
	CPlayerPed(int, bool);
	virtual ~CPlayerPed();
	
	void SetWantedLevel(int a2);
	static void SetupPlayerPed(int a_iIndex);
	static void RemovePlayerPed(int a_iIndex);
	
};

#endif