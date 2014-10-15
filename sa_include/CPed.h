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
};

#endif