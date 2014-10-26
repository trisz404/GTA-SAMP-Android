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
		l_pNetGame->getPlayerPool()->GetLocalPlayer()->CreateGTAPlayer();
		
		
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