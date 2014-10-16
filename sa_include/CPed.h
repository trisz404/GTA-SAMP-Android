#ifndef __CPED_H__
#define __CPED_H__

#include "CPhysical.h"
#include "CVector.h"

class CPed : public CPhysical
{
private:
	int reverse_me;
	
public:
	CPed();
	virtual ~CPed();
	virtual void Add(void);
	virtual void /*Add(CRect const&);*/ dummy();
	virtual void Remove(void);
	virtual void SetIsStatic(bool);
	virtual void SetModelIndex(unsigned int);
	virtual void SetModelIndexNoCreate(unsigned int);
	virtual void CreateRwObject(void);
	virtual void DeleteRwObject(void);
	virtual void GetBoundRect(void);const
	virtual void ProcessControl(void);
	virtual void ProcessCollision(void);
	virtual void ProcessShift(void);
	virtual void TestCollision(bool);	
	virtual void Teleport(CVector, unsigned char);
	virtual void SpecialEntityPreCollisionStuff(CPhysical *, bool, bool &, bool &, bool &, bool &);
	virtual void SpecialEntityCalcCollisionSteps(bool &, bool &);
	virtual void PreRender(void);
	virtual void Render(void);
	virtual void SetupLighting(void);
	virtual void RemoveLighting(bool);
	virtual void FlagToDestroyWhenNextProcessed(void);
	virtual void /*ProcessEntityCollision(CEntity *, CColPoint *);*/ dummy2();
	virtual void SetMoveAnim(void);
	virtual void Save(void);
	virtual void Load(void);
	
};

#endif