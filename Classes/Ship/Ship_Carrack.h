#ifndef __SHIP_CARRACK_H__
#define __SHIP_CARRACK_H__

#include "cocos2d.h"
#include "ShipBase.h"

class Ship_Carrack : public ShipBase
{
public:
	Ship_Carrack();
	~Ship_Carrack();

	virtual void UpdateShip(float dt);
	virtual void InitShip();

	virtual void ShipStopStart()override;
	virtual void ShipStopUpdate(float dt)override;
	virtual void ShipStopEnd()override;

	virtual void ShipMoveStart()override;
	virtual void ShipMoveUpdate(float dt)override;
	virtual void ShipMoveEnd()override;

	virtual void ShipAttackRightStart()override;
	virtual void ShipAttackRightUpdate(float dt)override;
	virtual void ShipAttackRightEnd()override;

	virtual void ShipAttackLeftStart()override;
	virtual void ShipAttackLeftUpdate(float dt)override;
	virtual void ShipAttackLeftEnd()override;

	virtual void ShipHurtStart()override;
	virtual void ShipHurtUpdate(float dt)override;
	virtual void ShipHurtEnd()override;

	virtual void ShipDieStart()override;
	virtual void ShipDieUpdate(float dt)override;
	virtual void ShipDieEnd()override;
	//------
	virtual void Move()override;

	virtual void Stop()override;

	virtual void TurnLeft()override;

	virtual void TurnRight()override;

	virtual void AttackLeft()override;

	virtual void AttackRight()override;
	//------
	virtual void EatItem(/*ItemType tItem*/)override;
	////  Controller!
	virtual void ShipBattleCtrl(ShipCtrlType t) override;

	//////////////////////////////////////////////////////////////////////////
	//
	//		Vehicle 的重载部分
	//
	//////////////////////////////////////////////////////////////////////////

	virtual void InitData();
};

#endif //
