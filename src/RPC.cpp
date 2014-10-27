#include <RakClient.h>
#include <RakNetworkFactory.h>
#include <PacketEnumerations.h>
#include <StringCompressor.h>

#include "types.h"
#include "RPC.h"
#include "CNetGame.h"


int log(const char *format, ...);


void ServerJoin(RPCParameters *rpcParams)
{
	RakNet::BitStream l_bitStream(rpcParams->input, rpcParams->numberOfBitsOfData/8 + 1, false);
	_PlayerID 		l_PlayerID;
	char			l_cIsNPC;
	unsigned char	l_ucNickLen;
	char			l_szNickName[256];
	unsigned int 	l_uiColor;
	CNetGame*		l_pNetGame;
	
	l_pNetGame = CNetGame::Instance();	
	
	l_bitStream.Read(l_PlayerID);
	l_bitStream.Read(l_uiColor);
	l_bitStream.Read(l_cIsNPC);
	l_bitStream.Read(l_ucNickLen);	
	l_bitStream.Read(l_szNickName, l_ucNickLen);

	l_pNetGame->getPlayerPool()->New(l_PlayerID, l_szNickName, (bool)l_cIsNPC);
	
	
	log("ServerJoin -> %s (%d)!", l_szNickName, l_PlayerID);
}

void ServerQuit(RPCParameters *rpcParams)
{
	log("ServerQuit called!");
}

int g_iNetModeNormalOnfootSendRate;

void InitGame(RPCParameters *rpcParams)
{
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsInitGame((unsigned char *)rpcParams->input,(iBitLength/8)+1,false);

	bool bLanMode, bStuntBonus;

	bool m_bZoneNames, m_bUseCJWalk, m_bAllowWeapons, m_bLimitGlobalChatRadius;
	float m_fGlobalChatRadius, m_fNameTagDrawDistance;
	bool m_bDisableEnterExits, m_bNameTagLOS, m_bTirePopping;
	int m_iSpawnsAvailable;
	bool m_bShowPlayerTags;
	int m_iShowPlayerMarkers;
	BYTE m_byteWorldTime, m_byteWeather;
	float m_fGravity;
	int m_iDeathDropMoney;
	bool m_bInstagib;
	CNetGame* l_pNetGame;

	log("InitGame() -> Called");

	
	l_pNetGame = CNetGame::Instance();
	

	bsInitGame.ReadCompressed(m_bZoneNames);
	bsInitGame.ReadCompressed(m_bUseCJWalk);
	bsInitGame.ReadCompressed(m_bAllowWeapons);
	bsInitGame.ReadCompressed(m_bLimitGlobalChatRadius);
	bsInitGame.Read(m_fGlobalChatRadius);
	bsInitGame.ReadCompressed(bStuntBonus);
	bsInitGame.Read(m_fNameTagDrawDistance);
	bsInitGame.ReadCompressed(m_bDisableEnterExits);
	bsInitGame.ReadCompressed(m_bNameTagLOS);
	bsInitGame.ReadCompressed(m_bTirePopping); // 
	bsInitGame.Read(m_iSpawnsAvailable);
	
	_PlayerID MyPlayerID;
	bsInitGame.Read(MyPlayerID);
		
	bsInitGame.ReadCompressed(m_bShowPlayerTags);
	bsInitGame.Read(m_iShowPlayerMarkers);
	bsInitGame.Read(m_byteWorldTime);
	bsInitGame.Read(m_byteWeather);
	bsInitGame.Read(m_fGravity);
	bsInitGame.ReadCompressed(bLanMode);
	bsInitGame.Read(m_iDeathDropMoney);
	bsInitGame.ReadCompressed(m_bInstagib); // 

	// Server's send rate restrictions
	bsInitGame.Read(g_iNetModeNormalOnfootSendRate);
	int iNetModeNormalIncarSendRate;
	bsInitGame.Read(iNetModeNormalIncarSendRate);
	int iNetModeFiringSendRate;
	bsInitGame.Read(iNetModeFiringSendRate);
	int iNetModeSendMultiplier;
	bsInitGame.Read(iNetModeSendMultiplier);

	int g_lagcompmode;
	bsInitGame.Read(g_lagcompmode);

	BYTE byteStrLen;
	bsInitGame.Read(byteStrLen);
	char g_szHostName[256];
	if(byteStrLen)
	{
		memset(g_szHostName,0,sizeof(g_szHostName));
		bsInitGame.Read(g_szHostName, byteStrLen);
	}
	g_szHostName[byteStrLen] = '\0';

	char byteVehicleModels[212];
	bsInitGame.Read(byteVehicleModels, 212);
	
	l_pNetGame->getPlayerPool()->setLocalPlayerID(MyPlayerID);	
	
	log("Connected to %.64s", g_szHostName);
}

void WorldPlayerAdd(RPCParameters *rpcParams)
{
	CNetGame::Instance()->getPlayerPool()->StreamPlayerIn(rpcParams);
	log("WorldPlayerAdd called!");
}

void WorldPlayerDeath(RPCParameters *rpcParams)
{
	log("WorldPlayerDeath called!");
}

void WorldPlayerRemove(RPCParameters *rpcParams)
{
	log("WorldPlayerRemove called!");
}

void WorldVehicleAdd(RPCParameters *rpcParams)
{
	log("WorldVehicleAdd called!");
}

void WorldVehicleRemove(RPCParameters *rpcParams)
{
	log("WorldVehicleRemove called!");
}

void ConnectionRejected(RPCParameters *rpcParams)
{
	log("ConnectionRejected called!");
}

void ClientMessage(RPCParameters *rpcParams)
{
	log("ClientMessage called!");
}

void Chat(RPCParameters *rpcParams)
{
	log("Chat called!");
}

void UpdateScoresPingsIPs(RPCParameters *rpcParams)
{
	log("UpdateScoresPingsIPs called!");
}

void ScrInitMenu(RPCParameters *rpcParams)
{
	log("ScrInitMenu called!");
}

void ScrDialogBox(RPCParameters *rpcParams)
{
	log("ScrDialogBox called!");
}

void ScrGameText(RPCParameters *rpcParams)
{
	int iBitLength = rpcParams->numberOfBitsOfData;

	RakNet::BitStream bsData((unsigned char *)rpcParams->input,(iBitLength/8)+1,false);
	char szMessage[400];
	int iType, iTime, iLength;

	bsData.Read(iType);
	bsData.Read(iTime);
	bsData.Read(iLength);

	if(iLength > 400) return; // tsk tsk, kye

	bsData.Read(szMessage, iLength);
	szMessage[iLength] = '\0';

	log("[GAMETEXT] %s", szMessage);
}

void ScrPlayAudioStream(RPCParameters *rpcParams)
{
	log("ScrPlayAudioStream called!");
}

void RegisterRPCs(RakClientInterface *pRakClient)
{
	REGISTER_STATIC_RPC(pRakClient, ServerJoin);
	REGISTER_STATIC_RPC(pRakClient, ServerQuit);
	REGISTER_STATIC_RPC(pRakClient, InitGame);
	REGISTER_STATIC_RPC(pRakClient, WorldPlayerAdd);
	REGISTER_STATIC_RPC(pRakClient, WorldPlayerDeath);
	REGISTER_STATIC_RPC(pRakClient, WorldPlayerRemove);
	REGISTER_STATIC_RPC(pRakClient, WorldVehicleAdd);
	REGISTER_STATIC_RPC(pRakClient, WorldVehicleRemove);
	REGISTER_STATIC_RPC(pRakClient, ConnectionRejected);
	REGISTER_STATIC_RPC(pRakClient, ClientMessage);
	REGISTER_STATIC_RPC(pRakClient, Chat);
	REGISTER_STATIC_RPC(pRakClient, UpdateScoresPingsIPs);
	
	REGISTER_STATIC_RPC(pRakClient, ScrInitMenu);
	REGISTER_STATIC_RPC(pRakClient, ScrDialogBox);
	REGISTER_STATIC_RPC(pRakClient, ScrGameText);
	REGISTER_STATIC_RPC(pRakClient, ScrPlayAudioStream);
}