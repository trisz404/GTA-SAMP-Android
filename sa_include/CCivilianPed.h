#ifndef __CCIVILIANPED_H__
#define __CCIVILIANPED_H__

#include "CPed.h"

enum ePedType
{
	ePedType_UNKNOWN = 0x13
};

class CCivilianPed : public CPed
{
	public:
	
	CCivilianPed(ePedType a_iType, unsigned int a_iModelIndex);
	~CCivilianPed();	
};


#endif