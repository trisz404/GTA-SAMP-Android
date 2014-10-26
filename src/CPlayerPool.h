#ifndef __CPLAYERPOOL_H__
#define __CPLAYERPOOL_H__

#include "types.h"
#include "CPlayer.h"

#define MAX_PLAYERS 1004


class CPlayerPool
{
public:

	CPlayerPool();
	~CPlayerPool();

	bool New(_PlayerID a_PlayerID, char* a_szNickName, bool a_bIsNPC);
	bool Delete(_PlayerID a_PlayerID);
	
	bool isPlayerConnected(_PlayerID a_PlayerID);	
	void setLocalPlayerID(_PlayerID a_PlayerID);
	
	void ProcessPlayerSync(Packet* a_pPacket);
	
	CPlayer* GetPlayer(int id) { return m_Players[id]; }
private:
	CPlayer*		m_Players[MAX_PLAYERS];
	_PlayerID		m_LocalPlayerID;


};


#endif