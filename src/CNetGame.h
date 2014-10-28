#ifndef __CNETGAME_H__
#define __CNETGAME_H__

#include <RakClient.h>
#include <RakNetworkFactory.h>
#include <PacketEnumerations.h>
#include <StringCompressor.h>

#include "CPlayerPool.h"

class CNetGame
{
/*private*/public: //TODO!!!
	static CNetGame*		m_SingletonInstance;
	RakClientInterface* 	m_rakClientInterface = nullptr;
	CPlayerPool*			m_PlayerPool = nullptr;
	bool					m_isInGame = false;
	
public:
	CNetGame();
	~CNetGame();

	void DbgConnect();
	void Process();
	
	/* Packets */
	void Packet_AUTH_KEY(Packet *p);
	void Packet_ConnectionSucceeded(Packet *p);
	
	RakClientInterface* getRakInterface();
	CPlayerPool*		getPlayerPool();
	
	void DoSync();
	
	static CNetGame* Instance()
	{
		if(m_SingletonInstance == nullptr)
		{
			m_SingletonInstance = new CNetGame();
		}
		return m_SingletonInstance;
	}
};

#endif