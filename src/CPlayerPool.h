#ifndef __CPLAYERPOOL_H__
#define __CPLAYERPOOL_H__

#include "types.h"
#include "CPlayer.h"
#include "CLocalPlayer.h"

#define MAX_PLAYERS 1004


class CPlayerPool
{
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
	
private:
	CLocalPlayer*	m_LocalPlayer;
	CPlayer*		m_Players[MAX_PLAYERS];
	_PlayerID		m_LocalPlayerID;


};


#endif