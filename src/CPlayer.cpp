#include "CPlayer.h"
#include <string.h>
#include "utils.h"

CPlayer::CPlayer()
{
	/*
	m_pPed = new CPlayerPed(1, true);
	*(unsigned int*)((char *) (m_pPed) + 1432) = 2; //Set type to network player
	*/
	
	CStreaming::RequestSpecialModel(0, "player", 26);
	CStreaming::LoadAllRequestedModels(true);	
	
	log("Creating CPed ...");
	m_pPed = new CPed(2);
	log("CPed created -> 0x%08X", m_pPed);
	m_pPed->SetModelIndex(0);
	m_pPed->SetPedState(PED_IDLE);
	// How can we disable the AI?
	
	// DEBUG PLAYER SPAWN...
	CWorld::Add(m_pPed);
	m_pPed->Teleport(CVector(1.0f, 0.0f, 3.0f), 0);
}

CPlayer::~CPlayer()
{
	if(m_pPed)
	{
		// CWorld::Remove(m_pPed);
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

void CPlayer::ProcessPlayerSync(Packet* a_pPacket)
{
	RakNet::BitStream 	l_BitStream(a_pPacket->data, a_pPacket->length, false);
	bool				l_bIsDataSynced;
	unsigned char		l_ucCompressedHealthAndArmour;
	
	l_BitStream.IgnoreBits(8); // PacketID
	l_BitStream.IgnoreBits(sizeof(_PlayerID) * 8); // PlayerID
	
	log("Proccess Sync...");
	
	if(!m_pPed || !m_pPed->m_pMatrix)
		return;
		
	CWorld::Remove(m_pPed);
	
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
	l_BitStream.Read(m_pPed->m_pMatrix->m_RwMatrix.pos.x);
	l_BitStream.Read(m_pPed->m_pMatrix->m_RwMatrix.pos.y);
	l_BitStream.Read(m_pPed->m_pMatrix->m_RwMatrix.pos.z);

	// Rotation
	/*l_BitStream.ReadNormQuat(
		m_onFootSyncData.quaterRotation[0],
		m_onFootSyncData.quaterRotation[1],
		m_onFootSyncData.quaterRotation[2],
		m_onFootSyncData.quaterRotation[3]
	);*/
	
	/*l_BitStream.ReadOrthMatrix(
		m_pPed->m_pMatrix->m_RwMatrix.right.x, m_pPed->m_pMatrix->m_RwMatrix.right.y, m_pPed->m_pMatrix->m_RwMatrix.right.z,
		m_pPed->m_pMatrix->m_RwMatrix.up.x, m_pPed->m_pMatrix->m_RwMatrix.up.y, m_pPed->m_pMatrix->m_RwMatrix.up.z,
		m_pPed->m_pMatrix->m_RwMatrix.at.x, m_pPed->m_pMatrix->m_RwMatrix.at.y, m_pPed->m_pMatrix->m_RwMatrix.at.z
	);*/
	
	// The ReadNormQuat crash the game. :S 
	l_BitStream.IgnoreBits(4 * 1 + 3 * 4 * 8);
	
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
	
	CWorld::Add(m_pPed);
}

void CPlayer::StreamIn(RPCParameters *rpcParams)
{
	int i;
	RakNet::BitStream 	l_BitStream(rpcParams->input, rpcParams->numberOfBitsOfData / 8 + 1, false);

	l_BitStream.IgnoreBits(sizeof(_PlayerID) * 8); // PlayerID
	
	/* Team ID */
	l_BitStream.Read(m_iTeamID);
	/* Skin ID*/
	l_BitStream.Read(m_iSkinID);
	
	/* Position */
	l_BitStream.Read(m_onFootSyncData.position.x);
	l_BitStream.Read(m_onFootSyncData.position.y);
	l_BitStream.Read(m_onFootSyncData.position.z);
	
	/* Facing angle */
	l_BitStream.Read(m_fFacingAngle);
	
	/* NickName color */
	l_BitStream.Read(m_uiNickColor);
	
	/* Fighting Style */
	l_BitStream.Read(m_iFightingStyle);
	
	/* Skill Levels */
	for(i = 0; i < MAX_SKILL_LEVEL; i++)
	{
		l_BitStream.Read(m_iSkillLevel[i]);
	}
	

	m_bIsStreamed = true;
	WorldAdd();
}

void CPlayer::StreamOut()
{
	m_bIsStreamed = false;
	WorldRemove();
}

void CPlayer::WorldAdd()
{

}

void CPlayer::WorldRemove()
{

}
