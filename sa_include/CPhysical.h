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
};

#endif