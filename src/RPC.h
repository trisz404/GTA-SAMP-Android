#ifndef __RPC_H__
#define __RPC_H__

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

void ServerJoin(RPCParameters *rpcParams);
void ServerQuit(RPCParameters *rpcParams);
void InitGame(RPCParameters *rpcParams);
void WorldPlayerAdd(RPCParameters *rpcParams);
void WorldPlayerDeath(RPCParameters *rpcParams);
void WorldPlayerRemove(RPCParameters *rpcParams);
void WorldVehicleAdd(RPCParameters *rpcParams);
void WorldVehicleRemove(RPCParameters *rpcParams);
void ConnectionRejected(RPCParameters *rpcParams);
void ClientMessage(RPCParameters *rpcParams);
void Chat(RPCParameters *rpcParams);
void UpdateScoresPingsIPs(RPCParameters *rpcParams);
void ScrInitMenu(RPCParameters *rpcParams);
void ScrDialogBox(RPCParameters *rpcParams);
void ScrGameText(RPCParameters *rpcParams);
void ScrPlayAudioStream(RPCParameters *rpcParams);
void RegisterRPCs(RakClientInterface *pRakClient);


#endif