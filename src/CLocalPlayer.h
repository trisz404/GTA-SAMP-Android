#ifndef __CLOCALPLAYER_H__
#define __CLOCALPLAYER_H__

#include "types.h"
#include <GTASA.h>

class CLocalPlayer
{
private:
	CPlayerPed*		m_GTAPlayerPed = nullptr;
	
public:
	CLocalPlayer();
	~CLocalPlayer();

	CPlayerPed*			CreateGTAPlayer();
	CPlayerPed* 		GetGTAPlayer();
};



#endif