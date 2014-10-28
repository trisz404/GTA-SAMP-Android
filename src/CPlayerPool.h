#ifndef __CPLAYERPOOL_H__
#define __CPLAYERPOOL_H__

#include "types.h"
#include "CPlayer.h"
#include "CLocalPlayer.h"

#define MAX_PLAYERS 1004


class CPlayerPool
{
private:
	CLocalPlayer*	m_LocalPlayer = nullptr;
	CPlayer*		m_Players[MAX_PLAYERS] = { 0 };
	_PlayerID		m_LocalPlayerID = -1;
	
public:
	CPlayerPool();
	~CPlayerPool();

	bool 			New(_PlayerID a_PlayerID, char* a_szNickName, bool a_bIsNPC);
	bool 			Delete(_PlayerID a_PlayerID);
	CPlayer*		GetPlayer(_PlayerID a_PlayerID);
	CLocalPlayer*	GetLocalPlayer();
	
	
	bool isPlayerConnected(_PlayerID a_PlayerID);	
	void setLocalPlayerID(_PlayerID a_PlayerID);
	
	void ProcessPlayerSync(Packet* a_pPacket);
	
	void StreamPlayerIn(RPCParameters *rpcParams);
};


#endif