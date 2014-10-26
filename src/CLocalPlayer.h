#ifndef __CLOCALPLAYER_H__
#define __CLOCALPLAYER_H__

#include "types.h"
#include <GTASA.h>

class CLocalPlayer
{
public:

	CLocalPlayer();
	~CLocalPlayer();

	void CreateGTAPlayer();

private:

	CPlayerPed*		m_GTAPlayerPed;

};



#endif