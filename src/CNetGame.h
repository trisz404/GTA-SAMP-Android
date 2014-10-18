#ifndef __CNETGAME_H__
#define __CNETGAME_H__

class CNetGame
{
public:
	CNetGame()
	{
		m_rakClientInterface = RakNetworkFactory::GetRakClientInterface();
	}
	
	~CNetGame()
	{
		RakNetworkFactory::DestroyRakClientInterface(m_rakClientInterface);
	}

	void DbgConnect()
	{
		m_rakClientInterface->Connect("192.168.1.246", 7777, 0, 0, 0);
	}
	
	
	RakClientInterface* getRakInterface()
	{
		return m_rakClientInterface;
	}
	
private:

	RakClientInterface* 	m_rakClientInterface;



};


#endif