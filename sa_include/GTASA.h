#ifndef __GTASA_H__
#define __GTASA_H__

#include <rwcore.h>

#include "CCivilianPed.h"
#include "CClothes.h"
#include "CCredits.h"
#include "CEntity.h"
#include "CFont.h"
#include "CHud.h"
#include "CLoadingScreen.h"
#include "CMatrix.h"
#include "CMessages.h"
#include "CObject.h"
#include "CPed.h"
#include "CPhysical.h"
#include "CPlaceable.h"
#include "CPlayerPed.h"
#include "CPopCycle.h"
#include "CRect.h"
#include "CRGBA.h"
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
void AsciiToGxtChar(const char*, unsigned short *);
void TemporaryFPSVisualization();
void emu_GammaSet(unsigned char);

#endif