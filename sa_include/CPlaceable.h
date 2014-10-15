#ifndef __CPLACEABLE_H__
#define __CPLACEABLE_H__

struct Placement
{
	RwV3d pos;
	float angle;
};

class CPlaceable
{
private:
	Placement m_Placement;
	int m_pMatrix;
	
public:
	CPlaceable();
	virtual ~CPlaceable();
};

#endif