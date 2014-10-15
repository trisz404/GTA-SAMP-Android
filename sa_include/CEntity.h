#ifndef __CENTITY_H__
#define __CENTITY_H__

#include "CPlaceable.h"

class CEntity : public CPlaceable
{
private:
	int reverse_me;
	
public:
	CEntity();
	virtual ~CEntity();
	
	/*
	CEntity::Add(void)
	CEntity::Add(CRect const&)
	CEntity::Remove(void)
	CEntity::SetIsStatic(bool)
	CEntity::SetModelIndex(unsigned int)
	CEntity::SetModelIndexNoCreate(unsigned int)
	CEntity::CreateRwObject(void)
	CEntity::DeleteRwObject(void)
	CEntity::GetBoundRect(void)const
	CEntity::ProcessControl(void)
	CEntity::ProcessCollision(void)
	CEntity::ProcessShift(void)
	CEntity::TestCollision(bool)
	CEntity::Teleport(CVector, unsigned char)
	CEntity::SpecialEntityPreCollisionStuff(CPhysical *, bool, bool &, bool &, bool &, bool &)
	CEntity::SpecialEntityCalcCollisionSteps(bool &, bool &)
	CEntity::PreRender(void)
	CEntity::Render(void)
	CEntity::SetupLighting(void)
	CEntity::RemoveLighting(bool)
	CEntity::FlagToDestroyWhenNextProcessed(void)
	*/
};

#endif