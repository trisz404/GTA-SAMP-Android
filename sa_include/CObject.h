#ifndef __CObject_H__
#define __CObject_H__

#include "CRect.h"

class CObject : public CPhysical
{
public:

				CObject(int, bool);
	virtual 	~CObject();
	virtual void Add(void);
	virtual void Add(CRect const&);
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
	virtual void ProcessEntityCollision(CEntity*, CColPoint*);
	
	

	static CObject* Create(int, bool);


};




#endif