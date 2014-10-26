#include "CLocalPlayer.h"



CLocalPlayer::CLocalPlayer()
{
	m_GTAPlayerPed		= 0;
}

CLocalPlayer::~CLocalPlayer()
{
	if(m_GTAPlayerPed)
	{
		/*TODO: Remove the PlayerPed */ 
		m_GTAPlayerPed = 0;
	}
}


void CLocalPlayer::CreateGTAPlayer()
{
	CStreaming::RequestSpecialModel(0, "player", 26);
	CStreaming::LoadAllRequestedModels(true);
	
	CPlayerPed::SetupPlayerPed(0);
	CClothes::RebuildPlayer(CWorld::Players[0], false);
	
	
	m_GTAPlayerPed = CWorld::Players[0];
}