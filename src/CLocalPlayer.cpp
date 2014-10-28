#include "CLocalPlayer.h"

CLocalPlayer::CLocalPlayer()
{
	
}

CLocalPlayer::~CLocalPlayer()
{
	if(m_GTAPlayerPed)
	{
		/*TODO: Remove the PlayerPed */ 
		m_GTAPlayerPed = nullptr;
	}
}


CPlayerPed* CLocalPlayer::CreateGTAPlayer()
{
	CStreaming::RequestSpecialModel(0, "player", 26);
	CStreaming::LoadAllRequestedModels(true);
	
	CWorld::PlayerInFocus = 0;
	CPlayerPed::SetupPlayerPed(CWorld::PlayerInFocus);
	
	m_GTAPlayerPed = FindPlayerPed(-1);
	CClothes::RebuildPlayer(m_GTAPlayerPed, false);
	return m_GTAPlayerPed;
}

CPlayerPed* CLocalPlayer::GetGTAPlayer()
{
	return m_GTAPlayerPed;
}