#include <errno.h>
#include <GTASA.h>
#include "CNetGame.h"

int log(const char *format, ...);
unsigned int GetBaseAddress();
void ARMJMP(void* from, void* to);
void ARMBIGJMP(void* to, void* form);

class CAEPedSpeechAudioEntity { public: static void Initialise(CEntity *); };

class CTask
{
	
};

class CTaskSimplePlayerOnFoot : public CTask
{
public:
	char reverse_me[52];

	CTaskSimplePlayerOnFoot();
};

class CTaskComplexFacial : public CTask
{
public:
	char reverse_me[32];

	CTaskComplexFacial();
};

class CTaskManager
{
public:
	int reverse_me;

	void SetTask(CTask*, int, bool);
	void SetTaskSecondary(CTask*, int);
};

int CRunningScript__Process(void* p)
{
	static bool l_bProcessed =	false;
	
	if(l_bProcessed == false)
	{
		CNetGame* 	l_pNetGame = CNetGame::Instance();
		CPlayerPed*	l_pLocalPlayer;
	
		l_pLocalPlayer = l_pNetGame->getPlayerPool()->GetLocalPlayer()->CreateGTAPlayer();
		
		if(l_pLocalPlayer)
		{
			l_pLocalPlayer->Teleport(CVector(1.0f, 0.0f, 3.0f), 0);
		}
	
	
		
		
		// CWorld::Players[202] = new CPlayerPed(1, false);
		// CWorld::Add(CWorld::Players[202]);
		// CWorld::Players[202]->Teleport(CVector(1.0f, 0.0f, 3.0f), 0);
		
		// CObject* l_pObject = CObject::Create(3578, false);
		
		// if(l_pObject)
		// {
			// log("Teleporting object");
			// l_pObject->Teleport(CVector(10.0, 10.0, 3.0), 0);
		// }
		
		l_bProcessed = true;
	}
	return 0;
}

int CPopCycle__Update()
{
	// we do nothing !
	return 0;
}

void LoadingScreen_hook(char const* a1, char const* a2, char const* a3)
{
	log("LoadingScreen_hook(%s, %s, %s)", a1, a2, a3);
	
	CLoadingScreen::NewChunkLoaded();
}

class CRGBA
{
private:
	float r;
	float g;
	float b;
	float a;
	
public:
	CRGBA(unsigned char, unsigned char, unsigned char, unsigned char);
	~CRGBA();
};

void AsciiToGxtChar(const char*, unsigned short *);
class CFont
{
public:
	static void PrintString(float, float, unsigned short *);
	static void RenderFontBuffer();
	static float GetHeight(bool);
	
	static void SetFontStyle(unsigned char);
	static void SetBackground(unsigned char, unsigned char);
	static void SetBackgroundColor(CRGBA);
	static void SetWrapx(float);
	static void SetProportional(unsigned char);
	static void SetColor(CRGBA);
	static void SetEdge(signed char);
	static void SetDropColor(CRGBA);
	static void SetScale(float);
	static void SetOrientation(unsigned char);
};

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
	if(!FindPlayerPed(-1))
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
	PrintLine("X: %.1f Y: %.1f Z: %.1f A: %.1f", FindPlayerPed(-1)->m_Placement.pos.x, FindPlayerPed(-1)->m_Placement.pos.y, FindPlayerPed(-1)->m_Placement.pos.z, FindPlayerPed(-1)->m_Placement.angle);
	
	if (FindPlayerPed(-1)->m_pMatrix)
	{
		PrintLine("");
		PrintLine("right: X: %.1f Y: %.1f Z: %.1f", FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.right.x, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.right.y, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.right.z);
		PrintLine("flags: %X", FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.flags);
		PrintLine("up: X: %.1f Y: %.1f Z: %.1f", FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.up.x, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.up.y, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.up.z);
		PrintLine("at: X: %.1f Y: %.1f Z: %.1f", FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.at.x, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.at.y, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.at.z);
		PrintLine("pos: X: %.1f Y: %.1f Z: %.1f", FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.pos.x, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.pos.y, FindPlayerPed(-1)->m_pMatrix->m_RwMatrix.pos.z);
	}
	
	CPlayer * player = CNetGame::Instance()->getPlayerPool()->GetPlayer(1);
	if (player)
	{
		PrintLine("");
		PrintLine("X: %.1f Y: %.1f Z: %.1f", player->m_onFootSyncData.position.x, player->m_onFootSyncData.position.y, player->m_onFootSyncData.position.z);
	}
	
	PrintLine("");
	PrintLine("Tick: %i, lastOnFootSyncTick: %i", GetTickCount(), lastOnFootSyncTick);
	PrintLine("g_iNetModeNormalOnfootSendRate: %i", g_iNetModeNormalOnfootSendRate);
}

class CHud { public: static void DrawAfterFade(); };
void TemporaryFPSVisualization();
void emu_GammaSet(unsigned char);
class CMessages { public: static void Display(unsigned char); };
class CCredits { public: static void Render(); };

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
	ARMBIGJMP((void *)(&CRunningScript::Process), (void *)(CRunningScript__Process));
	
	// Remove population spawning
	ARMBIGJMP((void *)(CPopCycle::Update), (void *)(CPopCycle__Update));
	
	// Hook the loading screen function
	ARMBIGJMP((void *)(LoadingScreen), (void *)(LoadingScreen_hook));
	
	// Hook render
	ARMBIGJMP((void *)(Render2dStuffAfterFade), (void *)(Render2dStuffAfterFade_hook));
}