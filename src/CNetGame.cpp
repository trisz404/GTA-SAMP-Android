#include "CNetGame.h"
#include "RPC.h"
#include "AuthTable.h"

CNetGame* CNetGame::m_SingletonInstance = 0;


int log(const char *format, ...);


CNetGame::CNetGame()
{
	m_rakClientInterface = RakNetworkFactory::GetRakClientInterface();
	
	RegisterRPCs(m_rakClientInterface);	
}

CNetGame::~CNetGame()
{
	RakNetworkFactory::DestroyRakClientInterface(m_rakClientInterface);
}

void CNetGame::DbgConnect()
{
	//m_rakClientInterface->Connect("192.168.1.246", 7777, 0, 0, 0); // Balika
	m_rakClientInterface->Connect("192.168.0.35", 7777, 0, 0, 0); // Sasuke
}

void CNetGame::Process()
{
	Packet* pPacket = 0;
	while((pPacket = m_rakClientInterface->Receive()))
	{
		int packetId = pPacket->data[0];
		log("Packet received -> %d\n", packetId);
		
		switch(packetId) 
		{
			case ID_DISCONNECTION_NOTIFICATION: log("Disconnect notification recived!"); break;
			case ID_CONNECTION_LOST: log("Connection lost!"); break;
			case ID_MODIFIED_PACKET: log("Modified packet!"); break;
			case ID_CONNECTION_ATTEMPT_FAILED: log("Failed to connect!"); break;
			case ID_CONNECTION_REQUEST_ACCEPTED: log("Request accepted!"); Packet_ConnectionSucceeded(pPacket); break;
			case ID_AUTH_KEY: log("Auth key!"); Packet_AUTH_KEY(pPacket); break;
		}
	
		m_rakClientInterface->DeallocatePacket(pPacket);	
	}
}



RakClientInterface* CNetGame::getRakInterface()
{
	return m_rakClientInterface;
}

void CNetGame::Packet_AUTH_KEY(Packet *p)
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

	m_rakClientInterface->Send(&bsKey, SYSTEM_PRIORITY, RELIABLE, NULL);
}


#define SEND_RPC(networkObject, functionName, packet) { int rpcid = (RPC_##functionName); (networkObject)->RPC(&rpcid, &packet, HIGH_PRIORITY, RELIABLE, 0, FALSE, UNASSIGNED_NETWORK_ID, NULL); }
#include <ttmathuint.h>
#include <ttmathuint_x86.h>
#include <stdlib.h>

bool GenerateSerial(char* input, char** output, int* output_len, int key)
{
	ttmath::UInt<100> math;
	unsigned char sha_hash_bin[20];
	char sha_hash[41];
	std::string result;

	/* Hash the input with SHA-1 */
	
	CSHA1 raksha;
	raksha.Update((unsigned char *) input, strlen(input));
	raksha.Final();
	raksha.GetHash(sha_hash_bin);

	sha_hash[0] = '\0';
	for (int i = 0; i < sizeof(sha_hash_bin); ++i)
		sprintf(sha_hash, "%s%02X", sha_hash, sha_hash_bin[i]);
	sha_hash[sizeof(sha_hash)] = '\0';

	log(sha_hash);

	/* Encrypt the hash with ttmath */

	math.FromString(sha_hash, 16);
	math.SerialEncrypt(key);
	result = math.ToString(16);

	*output_len = result.length();
	*output = new char[*output_len+1];

	strcpy(*output, result.c_str());
	return true;
}

void gen_random(char *s, const int len)
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < len; ++i)
		s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];

	s[len] = 0;
}

void CNetGame::Packet_ConnectionSucceeded(Packet *p)
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
	
	char fucku[128];
	gen_random(fucku, 128);
	char* auth_bs;
	int AuthBSLen;
	GenerateSerial(fucku, &auth_bs, &AuthBSLen, 0x3E9);
	log(auth_bs);
	bsSend.Write((BYTE) AuthBSLen);
	bsSend.Write(auth_bs, AuthBSLen);
	
	char szClientVer[] = "0.3z-R1";
	const BYTE iClientVerLen = (sizeof(szClientVer)-1);
	bsSend.Write(iClientVerLen);
	bsSend.Write(szClientVer, iClientVerLen);

	SEND_RPC(m_rakClientInterface, ClientJoin, bsSend);
}






