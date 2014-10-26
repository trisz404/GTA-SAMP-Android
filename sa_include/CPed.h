#ifndef __CPED_H__
#define __CPED_H__

#include "CPhysical.h"
#include "CVector.h"

enum ePedState
{
	PED_NONE = 0,
	PED_IDLE,
	PED_LOOK_ENTITY,
	PED_LOOK_HEADING,
	PED_WANDER_RANGE,
	PED_WANDER_PATH,
	PED_SEEK_POSITION,
	PED_SEEK_ENTITY,
	PED_FLEE_POSITION,
	PED_FLEE_ENTITY,
	PED_PURSUE,
	PED_FOLLOW_PATH,
	PED_SNIPER_MODE,
	PED_ROCKETLAUNCHER_MODE,
	PED_DUMMY,
	PED_PAUSE,
	PED_ATTACK,
	PED_FIGHT,		// new close combat fist fight mode
	PED_FACE_PHONE,
	PED_MAKE_PHONECALL,
	PED_CHAT,
	PED_MUG,
	PED_AIMGUN,
	PED_AI_CONTROL,
	PED_SEEK_CAR, //24
	PED_SEEK_BOAT_POSITION,
	PED_FOLLOW_ROUTE,
	PED_CPR,
	PED_SOLICIT,
	PED_BUY_ICE_CREAM,
	PED_INVESTIGATE_EVENT,
	PED_EVADE_STEP,
	PED_ON_FIRE,
	PED_SUNBATHE,
	PED_FLASH,
	PED_JOG,
	PED_ANSWER_MOBILE,	
	PED_HANG_OUT,
	PED_STATES_NO_AI, // only put states after here that do not require AI, put other ones before this	
	PED_ABSEIL_FROM_HELI,
	PED_SIT,
	PED_JUMP,
	PED_FALL,
	PED_GETUP,
	PED_STAGGER,
	PED_EVADE_DIVE,
	PED_STATES_CAN_SHOOT, // only put states before here than ped can be shot during
	PED_ENTER_TRAIN, 
	PED_EXIT_TRAIN,
	PED_ARREST_PLAYER,
	PED_DRIVING, // 50
	PED_PASSENGER,
	PED_TAXI_PASSENGER,
	PED_OPEN_DOOR,
	PED_DIE,
	PED_DEAD,
	PED_CARJACK,
	PED_DRAGGED_FROM_CAR,
	PED_ENTER_CAR,
	PED_STEAL_CAR,
	PED_EXIT_CAR,
	PED_HANDS_UP,
	PED_ARRESTED,
	PED_DEPLOY_STINGER,
	
	PED_NUM_STATES
};

enum eMoveState
{
   PEDMOVE_NONE = 0,
   PEDMOVE_STILL,
   PEDMOVE_TURN_L,
   PEDMOVE_TURN_R,
   PEDMOVE_WALK,
   PEDMOVE_JOG,
   PEDMOVE_RUN,
   PEDMOVE_SPRINT
};

class CPed : public CPhysical
{
private:
	char reverse_me[1916]; // hack
	
public:
	CPed(unsigned int);
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
	
	void ClearAimFlag();
	void ClearLookFlag();
	void SetPedState(ePedState);
	void SetMoveState(eMoveState);
};

#endif