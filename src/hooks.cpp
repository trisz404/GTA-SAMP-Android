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


void CRunningScript__Process()
{
	static bool l_bProcessed =	false;
	log("CRunningScript__Process() -> Called");
	
	
	
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
}

void Test();
void callpatch(int from, int to);

void InitHooks()
{
	unsigned int l_uiBaseAddr;
	
	l_uiBaseAddr = GetBaseAddress();

	// Disable script loading (main.scm)
	/*unsigned int ajmp = ARMJMP(l_uiBaseAddr + 0x002B9256, l_uiBaseAddr + 0x002B9368);	
	memcpy_protect((unsigned char*)(l_uiBaseAddr + 0x002B9256), (unsigned char*)&ajmp, 4);*/
	
	// Hook CRunningScript::Process()
	

	/*unsigned int ajmp = ARMJMP((unsigned long)(void*)(&CRunningScript::Process), (unsigned int)CRunningScript__Process);	
	if(memcpy_protect((unsigned char*)(void*)(&CRunningScript::Process), (unsigned char*)&ajmp, 4) == 0)
	{
		log("InitHooks() -> CRunningScript::Process - Hooked !");
	}*/
	
	/*
	unsigned int ajmp = ARMJMP((unsigned int)(l_uiBaseAddr + 0x02B7A54), (unsigned int)CRunningScript__Process);	
	if(memcpy_protect((unsigned char*)(void*)(l_uiBaseAddr + 0x02B7A54), (unsigned char*)&ajmp, 4) == 0)
	{
		log("InitHooks() -> CRunningScript::Process - Hooked !");
	}
	*/
	Test();
	callpatch((int)(l_uiBaseAddr + 0x02B7A54), (int)CRunningScript__Process);
	

}