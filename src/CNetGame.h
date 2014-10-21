#ifndef __CNETGAME_H__
#define __CNETGAME_H__

#include <RakClient.h>
#include <RakNetworkFactory.h>
#include <PacketEnumerations.h>
#include <StringCompressor.h>


class CNetGame
{
public:

	CNetGame();
	~CNetGame();

	void DbgConnect();
	void Process();
	
	/* Packets */
	void Packet_AUTH_KEY(Packet *p);
	void Packet_ConnectionSucceeded(Packet *p);
	
	
	RakClientInterface* getRakInterface();
	
	static CNetGame* Instance()
	{
		if(m_SingletonInstance == 0)
		{
			m_SingletonInstance = new CNetGame();
		}
		return m_SingletonInstance;
	}	
private:
	static CNetGame*		m_SingletonInstance;
	RakClientInterface* 	m_rakClientInterface;
};





#endif