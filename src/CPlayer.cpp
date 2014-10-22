#include "CPlayer.h"
#include <string.h>

CPlayer::CPlayer()
{
	m_pszNickName 	= 0;
	m_bIsNPC		= false;
}

CPlayer::~CPlayer()
{
}

void CPlayer::setNickName(char* a_pszNickName)
{
	unsigned int l_uiNickNameLen;
	
	if(m_pszNickName)
	{
		delete [] m_pszNickName;
	}
	
	l_uiNickNameLen = strlen(a_pszNickName);	
	m_pszNickName = new char[l_uiNickNameLen + 1];
	
	strcpy(m_pszNickName, a_pszNickName);
}

void CPlayer::setNPC(bool a_bSet)
{
	m_bIsNPC = a_bSet;
}


void CPlayer::ProcessPlayerSync(Packet* a_pPacket)
{
	RakNet::BitStream 	l_BitStream(a_pPacket->data, a_pPacket->length, false);
	bool				l_bIsDataSynced;
	unsigned char		l_ucCompressedHealthAndArmour;
	
	l_BitStream.IgnoreBits(8); // PacketID
	l_BitStream.IgnoreBits(sizeof(_PlayerID) * 2); // PlayerID
	

	// Left & Right Keys on foot
	l_BitStream.Read(l_bIsDataSynced);	
	if(l_bIsDataSynced)
	{
		l_BitStream.Read(m_onFootSyncData.leftRightKeysOnfoot);
	}
	
	// Up & Down Keys on foot
	l_BitStream.Read(l_bIsDataSynced);	
	if(l_bIsDataSynced)
	{
		l_BitStream.Read(m_onFootSyncData.updownKeysOnfoot);
	}
	
	// Keys on foot
	l_BitStream.Read(m_onFootSyncData.keysOnfoot);
	
	// Position
	l_BitStream.Read(m_onFootSyncData.position.x);
	l_BitStream.Read(m_onFootSyncData.position.y);
	l_BitStream.Read(m_onFootSyncData.position.z);

	// Rotation
	l_BitStream.ReadNormQuat(m_onFootSyncData.quaterRotation.W,
		m_onFootSyncData.quaterRotation.X,
		m_onFootSyncData.quaterRotation.Y,
		m_onFootSyncData.quaterRotation.Z);

	l_BitStream.Read(l_ucCompressedHealthAndArmour);
	
	// Fetch Health
	m_onFootSyncData.health = ((l_ucCompressedHealthAndArmour >> 4) & 0x0F) * 7;
	// Fetch Armour
	m_onFootSyncData.armour = (l_ucCompressedHealthAndArmour & 0x0F) * 7;
	
	// Weapon
	l_BitStream.Read(m_onFootSyncData.weapon);
	// Special Action
	l_BitStream.Read(m_onFootSyncData.specialAction);
	
	// Velocity
	l_BitStream.ReadVector(m_onFootSyncData.velocity.x,
		m_onFootSyncData.velocity.y,
		m_onFootSyncData.velocity.z);

	// Surfing Object/Vehicle ID
	l_BitStream.Read(l_bIsDataSynced);	
	if(l_bIsDataSynced)
	{
		l_BitStream.Read(m_onFootSyncData.surfingVehicleID);
		l_BitStream.Read(m_onFootSyncData.surfingOffsets.x);
		l_BitStream.Read(m_onFootSyncData.surfingOffsets.y);
		l_BitStream.Read(m_onFootSyncData.surfingOffsets.z);
	}

	// Animation Index
	l_BitStream.Read(l_bIsDataSynced);	
	if(l_bIsDataSynced)
	{
		l_BitStream.Read(m_onFootSyncData.animationIndex);
	}	
}




















