#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <dlfcn.h>
#include <unistd.h>
#include <pthread.h>

#include <GTASA.h>

#include "hooks.h"

#include <RakClient.h>
#include <RakNetworkFactory.h>
#include <PacketEnumerations.h>
#include <StringCompressor.h>
#include "CNetGame.h"

#include "AuthTable.h"

enum
{
	RPC_ClientJoin = 25,
	RPC_WorldPlayerAdd = 32,
	RPC_ScrPlayAudioStream = 41,
	RPC_ScrDialogBox = 61,
	RPC_ScrGameText = 73,
	RPC_ScrInitMenu = 76,
	RPC_ClientMessage = 93,
	RPC_Chat = 101,
	RPC_ConnectionRejected = 130,
	RPC_ServerJoin = 137,
	RPC_ServerQuit,
	RPC_InitGame,
	RPC_UpdateScoresPingsIPs = 155,
	RPC_WorldPlayerRemove = 163,
	RPC_WorldVehicleAdd,
	RPC_WorldVehicleRemove,
	RPC_WorldPlayerDeath,
};

int log(const char *format, ...)
{
   va_list arg;
   int done;

   va_start (arg, format);

   char buf[2048];
   done = vsprintf (buf, format, arg);

   __android_log_write(ANDROID_LOG_INFO, "SA_HACK_LOG", buf);

   va_end (arg);

   return done;
}

#define _byteswap_ulong(x) __builtin_bswap32(x)
#define _byteswap_uint64(x) __builtin_bswap64(x)

void Packet_AUTH_KEY(Packet *p, RakClientInterface *pRakClient)
{
	char * auth_key = "";
	unsigned char byteAuthKeyLen;

	for (int i = 0; i < 1279; ++i)
	{
		if (strcmp((char*) (p->data + 2), AuthKeyTable[i][0]) == 0)
		{
			auth_key = AuthKeyTable[i][1];
			byteAuthKeyLen = strlen(auth_key);
			break;
		}
	}
	
	RakNet::BitStream bsKey;
	bsKey.Write((unsigned char)ID_AUTH_KEY);
	bsKey.Write(byteAuthKeyLen);
	bsKey.Write(auth_key, byteAuthKeyLen);

	log("AUTH_KEY IN = %s; OUT = %s", (char*) (p->data + 2), auth_key);

	pRakClient->Send(&bsKey, SYSTEM_PRIORITY, RELIABLE, NULL);
}


#define SEND_RPC(networkObject, functionName, packet) { int rpcid = (RPC_##functionName); (networkObject)->RPC(&rpcid, &packet, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL); }

void Packet_ConnectionSucceeded(Packet *p, RakClientInterface *pRakClient)
{
	RakNet::BitStream bsSuccAuth((unsigned char *)p->data, p->length, false);

	bsSuccAuth.IgnoreBits(8); // ID_CONNECTION_REQUEST_ACCEPTED
	bsSuccAuth.IgnoreBits(32); // binaryAddress
	bsSuccAuth.IgnoreBits(16); // port

	unsigned short myPlayerID;
	bsSuccAuth.Read(myPlayerID);

	// g_myPlayerID = myPlayerID;
	// playerInfo[myPlayerID].iIsConnected = 1;
	// strcpy(playerInfo[myPlayerID].szPlayerName, g_szNickName);

	unsigned int uiChallenge;
	bsSuccAuth.Read(uiChallenge);

	// settings.uiChallange = uiChallenge;

	log("Connected. Joining the game...");

	RakNet::BitStream bsSend;

	int iVersion = 4047;
	bsSend.Write(iVersion);
	
	BYTE byteMod = 1;
	bsSend.Write(byteMod);
	
	BYTE byteNameLen = (BYTE) strlen("Android");
	bsSend.Write(byteNameLen);
	bsSend.Write("Android", byteNameLen);
	
	unsigned int uiClientChallengeResponse = uiChallenge ^ iVersion;
	bsSend.Write(uiClientChallengeResponse);

	char* auth_bs = "3D1A1B7E73BD23A0517B01D6FBEA1886A1E7D945A99";
	BYTE byteAuthBSLen = (BYTE) strlen(auth_bs);
	bsSend.Write(byteAuthBSLen);
	bsSend.Write(auth_bs, byteAuthBSLen);
	
	char szClientVer[] = "0.3z-R1";
	const BYTE iClientVerLen = (sizeof(szClientVer)-1);
	bsSend.Write(iClientVerLen);
	bsSend.Write(szClientVer, iClientVerLen);

	SEND_RPC(pRakClient, ClientJoin, bsSend);
}

void ServerJoin(RPCParameters *rpcParams)
{
	log("ServerJoin called!");
}

void ServerQuit(RPCParameters *rpcParams)
{
	log("ServerQuit called!");
}

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
	
	unsigned short MyPlayerID;
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
	int iNetModeNormalOnfootSendRate;
	bsInitGame.Read(iNetModeNormalOnfootSendRate);
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

	log("Connected to %.64s", g_szHostName);
}

void WorldPlayerAdd(RPCParameters *rpcParams)
{
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

void *wantedthread(void* punused)
{
    while(gGameState != 9)
		sleep(1); 
	
    log("Game loaded!");

    ToggleDebugFPS();

    sleep(5);

	CWanted::SetMaximumWantedLevel(0);
    FindPlayerPed(-1)->SetWantedLevel(0);
	
	CNetGame NetGame;
	NetGame.DbgConnect();
	
	RegisterRPCs(NetGame.getRakInterface());
	
	while (true)
	{
		Packet* pPacket = 0;
		while((pPacket = NetGame.getRakInterface()->Receive()))
		{
			int packetId = pPacket->data[0];
			log("Packet received -> %d\n", packetId);
			
			switch(packetId) 
			{
				case ID_DISCONNECTION_NOTIFICATION: log("Disconnect notification recived!"); break;
				case ID_CONNECTION_LOST: log("Connection lost!"); break;
				case ID_MODIFIED_PACKET: log("Modified packet!"); break;
				case ID_CONNECTION_ATTEMPT_FAILED: log("Failed to connect!"); break;
				case ID_CONNECTION_REQUEST_ACCEPTED: log("Request accepted!"); Packet_ConnectionSucceeded(pPacket, NetGame.getRakInterface()); break;
				case ID_AUTH_KEY: log("Auth key!"); Packet_AUTH_KEY(pPacket, NetGame.getRakInterface()); break;
			}
		
			NetGame.getRakInterface()->DeallocatePacket(pPacket);	
		}
	}
	
	return 0;
}

void inithack()
{
    log("Starting thread...");
    pthread_t thread;
    pthread_create(&thread, NULL, wantedthread, 0);

	InitHooks();
	
}

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved);
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    // Get jclass with env->FindClass.
    // Register methods with env->RegisterNatives.
	
	inithack();

    return JNI_VERSION_1_6;
}