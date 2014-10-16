#include <errno.h>

#include <GTASA.h>

#define ARM_RET		0x4770


int log(const char *format, ...);
unsigned int GetBaseAddress();
int memcpy_protect(unsigned char* form, unsigned char* to, int len);
unsigned long ARMJMP(unsigned long from, unsigned long to);


class CRunningScript
{
public:
	static void Process();
};

class CStreaming
{
public:
	static int RequestSpecialModel(int, const char*, int);
	static int LoadRequestedModels();

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


void CRunningScript__Process()
{
	static bool l_bProcessed = false;
	
	if(l_bProcessed == false)
	{
		log("CRunningScript__Process() -> Step 1");
		CStreaming::RequestSpecialModel(0, "player", 26);
		log("CRunningScript__Process() -> Step 2");
		CStreaming::LoadRequestedModels();	
		log("CRunningScript__Process() -> Step 3");
		CPlayerPed::SetupPlayerPed(0);	
		log("CRunningScript__Process() -> Step 4");
		CClothes::RebuildPlayer(CWorld::Players[0], false);
		log("CRunningScript__Process() -> Step 5");
		log("CRASHASHASHASAHSH");
		
		
	
	
		l_bProcessed = true;
	}
}

void InitHooks()
{
	unsigned int l_uiBaseAddr;
	
	l_uiBaseAddr = GetBaseAddress();

	// Disable script loading (main.scm)
	unsigned int ajmp = ARMJMP(l_uiBaseAddr + 0x002B925E, l_uiBaseAddr + 0x002B9368);	
	memcpy_protect((unsigned char*)(l_uiBaseAddr + 0x002B925E), (unsigned char*)&ajmp, 4);
	
	// Hook CRunningScript::Process()
	
	ajmp = ARMJMP((unsigned long)CRunningScript::Process, (unsigned int)CRunningScript__Process);	
	memcpy_protect((unsigned char*)CRunningScript::Process, (unsigned char*)&ajmp, 4);
	
	
}