#include <errno.h>
#include <GTASA.h>
#include "CNetGame.h"

int log(const char *format, ...);
unsigned int GetBaseAddress();
void ARMJMP(void* from, void* to);
void ARMBIGJMP(void* to, void* form);

int CRunningScript__Process_hook(void* p)
{
	static bool l_bProcessed =	false;
	
	if(l_bProcessed == false)
	{
		l_bProcessed = true;
		
		CNetGame* 	l_pNetGame = CNetGame::Instance();
		CPlayerPed*	l_pLocalPlayer;
	
		l_pLocalPlayer = l_pNetGame->getPlayerPool()->GetLocalPlayer()->CreateGTAPlayer();
		
		if(l_pLocalPlayer)
		{
			l_pLocalPlayer->Teleport(CVector(0.0f, 0.0f, 3.0f), 0);
		}
	}
	
	return 0;
}

int CPopCycle__Update_hook()
{
	// we do nothing !
	return 0;
}

void LoadingScreen_hook(char const* a1, char const* a2, char const* a3)
{
	log("LoadingScreen_hook(%s, %s, %s)", a1, a2, a3);
	
	CLoadingScreen::NewChunkLoaded();
}

#define PrintLine(line, ...) \
{ \
	char Buffer[200]; \
	sprintf(Buffer, line, ##__VA_ARGS__); \
	unsigned short GxtCharBuffer[200]; \
	AsciiToGxtChar(Buffer, GxtCharBuffer); \
	CFont::PrintString(5.0f, 5.0f + l * CFont::GetHeight(false), GxtCharBuffer); \
	++l; \
}

unsigned int GetTickCount();
extern unsigned int lastOnFootSyncTick;
extern int g_iNetModeNormalOnfootSendRate;

void RenderSAMP()
{
	CPlayerPed* ped = FindPlayerPed(-1);
	if(!ped)
		return;
	
	CFont::SetFontStyle(1);
	CFont::SetBackground(0, 0);
	CFont::SetWrapx(500.0f);
	CFont::SetProportional(1);
	CFont::SetColor(CRGBA(0xFF, 0xFF, 0xFF, 0xFF));
	CFont::SetEdge(1);
	CFont::SetDropColor(CRGBA(0x00, 0x00, 0x00, 0xFF));
	CFont::SetScale(0.77);
	CFont::SetOrientation(1);
	
	float l = 0;
	PrintLine("X: %.1f Y: %.1f Z: %.1f A: %.1f", ped->m_Placement.pos.x, ped->m_Placement.pos.y, ped->m_Placement.pos.z, ped->m_Placement.angle);
	
	if (ped->m_pMatrix)
	{
		PrintLine("");
		PrintLine("right: X: %.1f Y: %.1f Z: %.1f", ped->m_pMatrix->m_RwMatrix.right.x, ped->m_pMatrix->m_RwMatrix.right.y, ped->m_pMatrix->m_RwMatrix.right.z);
		PrintLine("flags: %X", ped->m_pMatrix->m_RwMatrix.flags);
		PrintLine("up: X: %.1f Y: %.1f Z: %.1f", ped->m_pMatrix->m_RwMatrix.up.x, ped->m_pMatrix->m_RwMatrix.up.y, ped->m_pMatrix->m_RwMatrix.up.z);
		PrintLine("at: X: %.1f Y: %.1f Z: %.1f", ped->m_pMatrix->m_RwMatrix.at.x, ped->m_pMatrix->m_RwMatrix.at.y, ped->m_pMatrix->m_RwMatrix.at.z);
		PrintLine("pos: X: %.1f Y: %.1f Z: %.1f", ped->m_pMatrix->m_RwMatrix.pos.x, ped->m_pMatrix->m_RwMatrix.pos.y, ped->m_pMatrix->m_RwMatrix.pos.z);
	}
	
	// CPlayer * player = CNetGame::Instance()->getPlayerPool()->GetPlayer(1);
	// if (player)
	// {
		// PrintLine("");
		// PrintLine("X: %.1f Y: %.1f Z: %.1f", player->m_onFootSyncData.position.x, player->m_onFootSyncData.position.y, player->m_onFootSyncData.position.z);
	// }
	
	PrintLine("");
	PrintLine("Tick: %i, lastOnFootSyncTick: %i", GetTickCount(), lastOnFootSyncTick);
	PrintLine("g_iNetModeNormalOnfootSendRate: %i", g_iNetModeNormalOnfootSendRate);
}

void Render2dStuffAfterFade_hook()
{
	CHud::DrawAfterFade();
	TemporaryFPSVisualization();
	RenderSAMP();
	emu_GammaSet(1);
	CMessages::Display(0);
	CFont::RenderFontBuffer();
	CCredits::Render();
	emu_GammaSet(0);
}

void InitHooks()
{
	// Remove script processing
	ARMBIGJMP((void *)(&CRunningScript::Process), (void *)(CRunningScript__Process_hook));
	
	// Remove population spawning
	ARMBIGJMP((void *)(CPopCycle::Update), (void *)(CPopCycle__Update_hook));
	
	// Hook the loading screen function
	ARMBIGJMP((void *)(LoadingScreen), (void *)(LoadingScreen_hook));
	
	// Hook render
	ARMBIGJMP((void *)(Render2dStuffAfterFade), (void *)(Render2dStuffAfterFade_hook));
}