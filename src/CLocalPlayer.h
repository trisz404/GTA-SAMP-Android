#ifndef __CLOCALPLAYER_H__
#define __CLOCALPLAYER_H__

#include "types.h"
#include <GTASA.h>

class CLocalPlayer
{
public:

	CLocalPlayer();
	~CLocalPlayer();

	CPlayerPed*			CreateGTAPlayer();
	CPlayerPed* 		GetGTAPlayer();

private:

	CPlayerPed*		m_GTAPlayerPed;

};



#endif