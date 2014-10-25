#ifndef __GTASA_H__
#define __GTASA_H__

#include <rwcore.h>

#include "CClothes.h"
#include "CEntity.h"
#include "CLoadingScreen.h"
#include "CMatrix.h"
#include "CObject.h"
#include "CPed.h"
#include "CPhysical.h"
#include "CPlaceable.h"
#include "CPlayerPed.h"
#include "CPopCycle.h"
#include "CRect.h"
#include "CRunningScript.h"
#include "CStreaming.h"
#include "CVector.h"
#include "CVehicle.h"
#include "CWanted.h"
#include "CWorld.h"


extern int gGameState;
CPlayerPed* FindPlayerPed(int id);
void ToggleDebugFPS();

void Render2dStuffAfterFade();

#endif