#ifndef __GTASA_H__
#define __GTASA_H__

#include <rwcore.h>

#include "CEntity.h"
#include "CPed.h"
#include "CPhysical.h"
#include "CPlaceable.h"
#include "CPlayerPed.h"
#include "CWanted.h"

extern int gGameState;
CPlayerPed* FindPlayerPed(int id);
void ToggleDebugFPS();

#endif