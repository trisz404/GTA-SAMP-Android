#include "CPlayerPool.h"
#include "utils.h"

CPlayerPool::CPlayerPool()
{
	m_LocalPlayer = new CLocalPlayer();
}

CPlayerPool::~CPlayerPool()
{
	for(int i = 0; i < MAX_PLAYERS; i++)
	{
		if(m_Players[i])
		{
			delete m_Players[i];
			m_Players[i] = 0;		
		}
	}
	
	if(m_LocalPlayer)
	{
		delete m_LocalPlayer;
	}
}


bool CPlayerPool::New(_PlayerID a_PlayerID, char* a_szNickName, bool a_bIsNPC)
{
	CPlayer* 	l_pPlayer;
	if(isPlayerConnected(a_PlayerID) || a_PlayerID == m_LocalPlayerID) return false;
	
	l_pPlayer = new CPlayer();
	
	if(l_pPlayer)
	{
		l_pPlayer->setNickName(a_szNickName);
		l_pPlayer->setNPC(a_bIsNPC);
		
		m_Players[a_PlayerID] = l_pPlayer;
		return true;
	}
	
	return false;
}

bool CPlayerPool::Delete(_PlayerID a_PlayerID)
{
	if(!isPlayerConnected(a_PlayerID) || a_PlayerID == m_LocalPlayerID) return false;
	
	
	delete m_Players[a_PlayerID];
	m_Players[a_PlayerID] = 0;
	return true;
}

CPlayer* CPlayerPool::GetPlayer(_PlayerID a_PlayerID)
{
	if(isPlayerConnected(a_PlayerID))
	{
		return m_Players[a_PlayerID];
	}
	return nullptr;
}

CLocalPlayer* CPlayerPool::GetLocalPlayer()
{
	return m_LocalPlayer;
}

bool CPlayerPool::isPlayerConnected(_PlayerID a_PlayerID)
{
	if(a_PlayerID >= 0 && a_PlayerID < MAX_PLAYERS)
	{
		return m_Players[a_PlayerID] != 0;
	}
	
	return false;
}

void CPlayerPool::setLocalPlayerID(_PlayerID a_PlayerID)
{
	m_LocalPlayerID = a_PlayerID;
}

void CPlayerPool::ProcessPlayerSync(Packet* a_pPacket)
{
	RakNet::BitStream l_BitStream(a_pPacket->data, a_pPacket->length, false);
	_PlayerID 	l_PlayerID;
	
	l_BitStream.IgnoreBits(8); // PacketID
	l_BitStream.Read(l_PlayerID);
	
	log("Sync for: %i", l_PlayerID);
	
	if(isPlayerConnected(l_PlayerID))
	{
		m_Players[l_PlayerID]->ProcessPlayerSync(a_pPacket);
	}
}
void CPlayerPool::StreamPlayerIn(RPCParameters *rpcParams)
{
	RakNet::BitStream l_BitStream(rpcParams->input, rpcParams->numberOfBitsOfData / 8 + 1, false);
	_PlayerID 	l_PlayerID;
	
	l_BitStream.Read(l_PlayerID);
	
	if(isPlayerConnected(l_PlayerID))
	{
		m_Players[l_PlayerID]->StreamIn(rpcParams);
	}
}
