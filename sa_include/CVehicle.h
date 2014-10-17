#ifndef __CVEHICLE_H__
#define __CVEHICLE_H__

#include "CRect.h"

class CVehicle : public CEntity
{
public:

	~CVehicle();
	
	virtual void Add();
	virtual void Add(CRect const&);
	virtual void Remove();
	virtual void SetIsStatic(bool);
	virtual void SetModelIndex(unsigned int);
	virtual void SetModelIndexNoCreate(unsigned int);
	virtual void CreateRwObject();
	virtual void DeleteRwObject();
	virtual void GetBoundRect(); const
	virtual void ProcessControl();
	virtual void ProcessCollision();
	virtual void ProcessShift();
	virtual void TestCollision(bool);
	virtual void Teleport(CVector, unsigned char);
	virtual void SpecialEntityPreCollisionStuff(CPhysical*, bool, bool&, bool&, bool&, bool&);
	virtual void SpecialEntityCalcCollisionSteps(bool&, bool&);
	virtual void PreRender();
	virtual void Render();
	virtual void SetupLighting();
	virtual void RemoveLighting(bool);
	/*
	// I just assumed that theses method return void. (we have to search)
	virtual void FlagToDestroyWhenNextProcessed();
	virtual void ProcessEntityCollision(CEntity*, CColPoint*);
	virtual void ProcessControlCollisionCheck(bool);
	virtual void ProcessControlInputs(unsigned char);
	virtual void GetComponentWorldPosition(int, CVector&);
	virtual void IsComponentPresent(int); const
	virtual void OpenDoor(CPed*, int, eDoors, float, bool);
	virtual void ProcessOpenDoor(CPed*, unsigned int, unsigned int, unsigned int, float);
	virtual void GetDooorAngleOpenRatio(eDoors); const
	virtual void IsDoorReady(eDoors); const
	virtual void IsDoorFullyOpen(eDoors); const
	virtual void IsDoorClosed(eDoors); const
	virtual void IsDoorMissing(eDoors); const
	virtual void GetDooorAngleOpenRatio(unsigned int); const
	virtual void IsDoorReady(unsigned int); const
	virtual void IsDoorFullyOpen(unsigned int); const
	virtual void IsDoorClosed(unsigned int); const
	virtual void IsDoorMissing(unsigned int); const
	virtual void IsOpenTopCar(); const
	virtual void RemoveRefsToVehicle(CEntity*);
	virtual void BlowUpCar(CEntity*, unsigned char);
	virtual void BlowUpCarCutSceneNoExtras(bool, bool, bool, bool);
	virtual void SetUpWheelColModel(CColModel*);
	virtual void BurstTyre(unsigned char, bool);
	virtual void IsRoomForPedToLeaveCar(unsigned int, CVector*);
	virtual void ProcessDrivingAnims(CPed*, unsigned char);
	virtual void GetRideAnimData();
	virtual void SetupSuspensionLines();
	virtual void AddMovingCollisionSpeed(CVector&);
	virtual void Fix();
	virtual void SetupDamageAfterLoad();
	virtual void DoBurstAndSoftGroundRatios();
	virtual void GetHeightAboveRoad(); const
	virtual void PlayCarHorn();
	virtual void GetNumContactWheels();
	virtual void VehicleDamage(float, unsigned short, CEntity*, CVector*, CVector*, eWeaponType);
	virtual void CanPedStepOutCar(bool); const
	virtual void CanPedJumpOutCar(CPed*); const
	virtual void GetTowHitchPos(CVector&, bool, CVehicle*);
	virtual void GetTowBarPos(CVector&, bool, CVehicle*);
	virtual void SetTowLink(CVehicle*, bool);
	virtual void BreakTowLink();
	virtual void FindWheelWidth(bool);
	virtual void Save();
	virtual void Load();
	*/


};


#endif