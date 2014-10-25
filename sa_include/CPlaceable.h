#ifndef __CPLACEABLE_H__
#define __CPLACEABLE_H__

struct Placement
{
	RwV3d pos;
	float angle;
};

class CPlaceable
{
public:
	Placement m_Placement;
	CMatrixLink* m_pMatrix;
	
	CPlaceable();
	virtual ~CPlaceable();
};

#endif