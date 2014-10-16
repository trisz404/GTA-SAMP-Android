#ifndef __CPHYSICAL_H__
#define __CPHYSICAL_H__

#include "CEntity.h"

class CPhysical : public CEntity
{
private:
	int reverse_me;
	
public:
	CPhysical();
	virtual ~CPhysical();
	
	/*
	CPhysical::Add(void)
	CEntity::Add(CRect const&)
	CPhysical::Remove(void)
	CEntity::SetIsStatic(bool)
	CEntity::SetModelIndex(unsigned int)
	CEntity::SetModelIndexNoCreate(unsigned int)
	CEntity::CreateRwObject(void)
	CEntity::DeleteRwObject(void)
	CPhysical::GetBoundRect(void)const
	CPhysical::ProcessControl(void)
	CPhysical::ProcessCollision(void)
	CPhysical::ProcessShift(void)
	CPhysical::TestCollision(bool)
	CEntity::Teleport(CVector, unsigned char)
	CEntity::SpecialEntityPreCollisionStuff(CPhysical *, bool, bool &, bool &, bool &, bool &)
	CEntity::SpecialEntityCalcCollisionSteps(bool &, bool &)
	CEntity::PreRender(void)
	CEntity::Render(void)
	CEntity::SetupLighting(void)
	CEntity::RemoveLighting(bool)
	CEntity::FlagToDestroyWhenNextProcessed(void)
	CPhysical::ProcessEntityCollision(CEntity *, CColPoint *)
	*/
};

#endif