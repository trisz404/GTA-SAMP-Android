#include <errno.h>

#include <GTASA.h>

#define ARM_RET		0x4770


int log(const char *format, ...);
unsigned int GetBaseAddress();
void ARMJMP(void* from, void* to);
void ARMBIGJMP(void* to, void* form);

class CRunningScript
{
public:
	void Process();
};

class CStreaming
{
public:
	static int RequestSpecialModel(int, const char*, int);
	static int LoadAllRequestedModels(bool);

};


class CClothes
{
public:
	static void RebuildPlayer(CPlayerPed*, bool);
};



class CWorld
{
public:
	static CPlayerPed* Players[202];
};

int CRunningScript__Process(void* p)
{
	static bool l_bProcessed =	false;
	
	if(l_bProcessed == false)
	{
		log("CRunningScript__Process() -> Step 1");
		CStreaming::RequestSpecialModel(0, "player", 26);
		log("CRunningScript__Process() -> Step 2");
		CStreaming::LoadAllRequestedModels(true);	
		log("CRunningScript__Process() -> Step 3");
		CPlayerPed::SetupPlayerPed(0);	
		log("CRunningScript__Process() -> Step 4");
		CClothes::RebuildPlayer(CWorld::Players[0], false);
		log("CRunningScript__Process() -> Step 5");
		log("CRASHASHASHASAHSH");
		
		if(CWorld::Players[0])
		{
			log("CRunningScript__Process() -> Teleporting player !");			
			CWorld::Players[0]->Teleport(CVector(0.0f, 0.0f, 3.0f), 0);
		}
		else
		{
			log("CRunningScript__Process() -> Teleporting player failed, nullptr!");
		}
	
	
		l_bProcessed = true;
	}
	return 0;
}

class CLoadingScreen
{
public:
	static void NewChunkLoaded();
};

void LoadingScreen(char const*, char const*, char const*);
void LoadingScreen_hook(char const* a1, char const* a2, char const* a3)
{
	log("LoadingScreen_hook(%s, %s, %s)", a1, a2, a3);
	
	CLoadingScreen::NewChunkLoaded();
}

void InitHooks()
{
	unsigned int l_uiBaseAddr = GetBaseAddress();
	
	ARMBIGJMP((void *)(&CRunningScript::Process), (void *)CRunningScript__Process);
	
	ARMBIGJMP((void *)(LoadingScreen), (void *)(LoadingScreen_hook));
}