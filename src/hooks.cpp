#include <errno.h>
#include <GTASA.h>

int log(const char *format, ...);
unsigned int GetBaseAddress();
void ARMJMP(void* from, void* to);
void ARMBIGJMP(void* to, void* form);

int CRunningScript__Process(void* p)
{
	static bool l_bProcessed =	false;
	
	if(l_bProcessed == false)
	{
		CStreaming::RequestSpecialModel(0, "player", 26);
		CStreaming::LoadAllRequestedModels(true);	

		CPlayerPed::SetupPlayerPed(0);
		CClothes::RebuildPlayer(CWorld::Players[0], false);
		
		if(CWorld::Players[0])
		{
			log("CRunningScript__Process() -> Teleporting player !");			
			CWorld::Players[0]->Teleport(CVector(0.0f, 0.0f, 3.0f), 0);
			
			CObject* l_pObject = CObject::Create(3578, false);
			
			if(l_pObject)
			{
				log("Teleporting object");
				l_pObject->Teleport(CVector(10.0, 10.0, 3.0), 0);
			}			
		}
		else
		{
			log("CRunningScript__Process() -> Teleporting player failed, nullptr!");
		}	
	
		l_bProcessed = true;
	}
	return 0;
}

int CPopCycle__Update()
{
	// we do nothing !
	return 0;
}

void LoadingScreen(char const*, char const*, char const*);
void LoadingScreen_hook(char const* a1, char const* a2, char const* a3)
{
	log("LoadingScreen_hook(%s, %s, %s)", a1, a2, a3);
	
	CLoadingScreen::NewChunkLoaded();
}

void InitHooks()
{
	/* Remove script processing */
	ARMBIGJMP((void *)(&CRunningScript::Process), (void *)CRunningScript__Process);
	
	/* Remove population spawning */
	ARMBIGJMP((void*)CPopCycle::Update, (void*)CPopCycle__Update);
	
	/* Hook the loading screen function */
	ARMBIGJMP((void *)(LoadingScreen), (void *)(LoadingScreen_hook));
}