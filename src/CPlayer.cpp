#include "CPlayer.h"
#include <string.h>

CPlayer::CPlayer()
{
	m_pPed = new CPlayerPed(1, true);
	*(unsigned int*)((char *) (m_pPed) + 1432) = 2;
	
	CWorld::Add(m_pPed);
	
	m_pPed->Teleport(CVector(1.0f, 0.0f, 3.0f), 0);
}

CPlayer::~CPlayer()
{
	if(m_pPed)
	{
		CWorld::Remove(m_pPed);
		// delete m_pPed;
	}
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

int log(const char *format, ...);

void CPlayer::ProcessPlayerSync(Packet* a_pPacket)
{
	RakNet::BitStream 	l_BitStream(a_pPacket->data, a_pPacket->length, false);
	bool				l_bIsDataSynced;
	unsigned char		l_ucCompressedHealthAndArmour;
	
	l_BitStream.IgnoreBits(8); // PacketID
	l_BitStream.IgnoreBits(sizeof(_PlayerID) * 8); // PlayerID
	
	log("Proccess Sync...");
	
	// Left & Right Keys on foot
	l_BitStream.Read(l_bIsDataSynced);	
	if(l_bIsDataSynced)
	{
		l_BitStream.Read(m_onFootSyncData.leftRightKeysOnfoot);
	}
	
	log("Proccess Sync...");
	
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
	// l_BitStream.ReadNormQuat(m_onFootSyncData.quaterRotation.W, m_onFootSyncData.quaterRotation.X, m_onFootSyncData.quaterRotation.Y, m_onFootSyncData.quaterRotation.Z);
	
	// The ReadNormQuat crash the game. :S 
	l_BitStream.IgnoreBits(4 + 3 * 4 * 8);
	
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
	l_BitStream.ReadVector(m_onFootSyncData.velocity.x, m_onFootSyncData.velocity.y, m_onFootSyncData.velocity.z);

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
	
	if(m_pPed->m_pMatrix)
	{
		CWorld::Remove(m_pPed);

		/*m_pPed->m_pMatrix->m_RwMatrix.right.x = CWorld::Players[0]->m_pMatrix->m_RwMatrix.right.x;
		m_pPed->m_pMatrix->m_RwMatrix.right.y = CWorld::Players[0]->m_pMatrix->m_RwMatrix.right.y;
		m_pPed->m_pMatrix->m_RwMatrix.right.z = CWorld::Players[0]->m_pMatrix->m_RwMatrix.right.z;

		m_pPed->m_pMatrix->m_RwMatrix.flags = CWorld::Players[0]->m_pMatrix->m_RwMatrix.flags;

		m_pPed->m_pMatrix->m_RwMatrix.up.x = CWorld::Players[0]->m_pMatrix->m_RwMatrix.up.x;
		m_pPed->m_pMatrix->m_RwMatrix.up.y = CWorld::Players[0]->m_pMatrix->m_RwMatrix.up.y;
		m_pPed->m_pMatrix->m_RwMatrix.up.z = CWorld::Players[0]->m_pMatrix->m_RwMatrix.up.z;

		m_pPed->m_pMatrix->m_RwMatrix.at.x = CWorld::Players[0]->m_pMatrix->m_RwMatrix.at.x;
		m_pPed->m_pMatrix->m_RwMatrix.at.y = CWorld::Players[0]->m_pMatrix->m_RwMatrix.at.y;
		m_pPed->m_pMatrix->m_RwMatrix.at.z = CWorld::Players[0]->m_pMatrix->m_RwMatrix.at.z;*/

		m_pPed->m_pMatrix->m_RwMatrix.pos.x = m_onFootSyncData.position.x;
		m_pPed->m_pMatrix->m_RwMatrix.pos.y = m_onFootSyncData.position.y;
		m_pPed->m_pMatrix->m_RwMatrix.pos.z = m_onFootSyncData.position.z;

		CWorld::Add(m_pPed);
	}
}





















