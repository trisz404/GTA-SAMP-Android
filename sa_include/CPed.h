#ifndef __CPED_H__
#define __CPED_H__

#include "CPhysical.h"

class CPed : public CPhysical
{
private:
	int reverse_me;
	
public:
	CPed();
	virtual ~CPed();
	
	/*
	CPhysical::Add(void)
	CEntity::Add(CRect const&)
	CPhysical::Remove(void)
	CEntity::SetIsStatic(bool)
	CPed::SetModelIndex(unsigned int)
	CEntity::SetModelIndexNoCreate(unsigned int)
	CEntity::CreateRwObject(void)
	CPed::DeleteRwObject(void)
	CPhysical::GetBoundRect(void)const
	CPed::ProcessControl(void)
	CPhysical::ProcessCollision(void)
	CPhysical::ProcessShift(void)
	CPhysical::TestCollision(bool)
	CPed::Teleport(CVector, unsigned char)
	CPed::SpecialEntityPreCollisionStuff(CPhysical *, bool, bool &, bool &, bool &, bool &)
	CPed::SpecialEntityCalcCollisionSteps(bool &, bool &)
	CPed::PreRender(void)
	CPed::Render(void)
	CPed::SetupLighting(void)
	CPed::RemoveLighting(bool)
	CPed::FlagToDestroyWhenNextProcessed(void)
	CPed::ProcessEntityCollision(CEntity *, CColPoint *)
	CPed::SetMoveAnim(void)
	CPed::Save(void)
	CPed::Load(void)
	*/
};

#endif