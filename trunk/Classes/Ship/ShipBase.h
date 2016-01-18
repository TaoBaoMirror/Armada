#ifndef __SHIP_BASE_H__
#define __SHIP_BASE_H__

#include "cocos2d.h"

enum ShipCtrlType
{
	ShipCtrlType_Move = 0,
	ShipCtrlType_TurnLeft,
	ShipCtrlType_TurnRight,
	ShipCtrlType_FireLeft,
	ShipCtrlType_FireRight,
	//ShipCtrlType_Stop,
};

class ShipBase : public cocos2d::Sprite
{
protected:
	enum  ShipAnimType
	{
		ShipAnim_Stop = 0,
		ShipAnim_Move,
		ShipAnim_Attack_Right,
		ShipAnim_Attack_Left,
		ShipAnim_Hurt,
		ShipAnim_Die,
	};
public:
	ShipBase();
	~ShipBase();

	virtual void InitShip(){}

	virtual void update(float delta) override;

	void SetResource(std::string name);

	//------
	void ReBorn(); //¸´»î
	//------
	virtual void ShipStopStart(){}
	virtual void ShipStopUpdate(float dt){}
	virtual void ShipStopEnd(){}

	virtual void ShipMoveStart(){}
	virtual void ShipMoveUpdate(float dt){}
	virtual void ShipMoveEnd(){}

	virtual void ShipAttackRightStart(){}
	virtual void ShipAttackRightUpdate(float dt){}
	virtual void ShipAttackRightEnd(){}

	virtual void ShipAttackLeftStart(){}
	virtual void ShipAttackLeftUpdate(float dt){}
	virtual void ShipAttackLeftEnd(){}

	virtual void ShipHurtStart(){}
	virtual void ShipHurtUpdate(float dt){}
	virtual void ShipHurtEnd(){}

	virtual void ShipDieStart(){}
	virtual void ShipDieUpdate(float dt){}
	virtual void ShipDieEnd(){}
	//------
	virtual void Move(){}

	virtual void Stop(){}

	virtual void TurnLeft(){}

	virtual void TurnRight(){}

	virtual void AttackLeft(){}

	virtual void AttackRight(){}
	//------
	virtual void EatItem(/*ItemType tItem*/){}

	virtual void ShipBattleCtrl(ShipCtrlType type);

	//------

public:
	//ShipFSM* m_pFSM;

protected:
	std::map<std::string, cocos2d::Vector<cocos2d::SpriteFrame*>> m_framesDict;

	std::vector<std::string> ActionsName;

	cocos2d::ValueVector m_ActionsFrameCount;

	std::string m_ShipName;

	bool m_bIsMoving;

	cocos2d::Vec2 m_CurDirect;
};

#endif //__SHIP_BASE_H__
