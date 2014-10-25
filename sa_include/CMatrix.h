#ifndef __CMATRIX_H__
#define __CMATRIX_H__

class CMatrix
{
public:
	RwMatrix m_RwMatrix;
	char gap_3D[3];
	RwMatrix *m_pRwMatrix;
	int m_isRwAllocated;
};

class CPlaceable;
class CMatrixLink : public CMatrix
{
public:
	CPlaceable *m_pPlaceable;
	CMatrixLink *m_pPrev;
	CMatrixLink *m_pNext;
};

#endif