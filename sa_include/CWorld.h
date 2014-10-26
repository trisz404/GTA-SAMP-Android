#ifndef __CWORLD_H__
#define __CWORLD_H__

class CWorld
{
public:
	static int PlayerInFocus;
	
	static CPed* Players[202]; //83 is a special pad. 101 is 2nd, 202 is 3rd player ped.

	static void Add(CEntity *);
	static void Remove(CEntity *);
};

#endif