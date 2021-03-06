#ifndef __CPLAYER_H__
#define __CPLAYER_H__

#include "types.h"

#include <GTASA.h>
#include <RakClient.h>

#define MAX_SKILL_LEVEL 11

typedef struct ON_FOOT_SYNC_t // size 0x44
{
#pragma pack( 1 )
	uint16_t			leftRightKeysOnfoot;					// + 0x0000
	uint16_t			updownKeysOnfoot;						// + 0x0002
	uint16_t			keysOnfoot;								// + 0x0004
	CVector				position;								// + 0x0006 -> 0x000E
	float				quaterRotation[4];						// + 0x0012 -> 0x001E
	uint8_t				health;									// + 0x0022
	uint8_t				armour;									// + 0x0023
	uint8_t				weapon;									// + 0x0024
	uint8_t				specialAction;							// + 0x0025
	CVector				velocity;								// + 0x0026
	CVector				surfingOffsets;							// + 0x0032
	_VehicleID			surfingVehicleID;						// + 0x003E	
	uint32_t			animationIndex;							// + 0x0040
} ON_FOOT_SYNC;

class CPlayer
{
private:
	CPed*		 	m_pPed = nullptr;
	char*			m_pszNickName = "";
	bool			m_bIsStreamed = false;
	bool 			m_bIsNPC = false;	
	uint32_t		m_uiNickColor = 0;
	uint8_t			m_iTeamID = 0;
	int				m_iSkinID = 0;
	uint8_t			m_iFightingStyle = 0;
	uint16_t		m_iSkillLevel[MAX_SKILL_LEVEL] = { 0 };
	float			m_fFacingAngle = 0.0f;

public:
	CPlayer();
	~CPlayer();
	
	void setNickName(char* a_pszNickName);
	void setNPC(bool a_bSet);	
	
	void ProcessPlayerSync(Packet* a_pPacket);
	
	void StreamIn(RPCParameters *rpcParams);
	void StreamOut();
	
	void WorldAdd();
	void WorldRemove();
	
};



#endif