#include "Ship_Carrack.h"
#include "Drive/Vehicle.h"
#include "Drive/SteeringBehavior.h"
#include "BattleMap/BattleMapManager.h"
#include "Bullet/BulletEmitter.h"

Ship_Carrack::Ship_Carrack()
{
	//name
	m_ShipName = "Ship_Carrack_";
	//name
	std::string imgname[6] = { "Stop", "Move", "Attackleft", "Attackright", "Hurt", "Die" };
	//ActionsName = test; 
	for (int i = 0; i < 6; ++i)
	{
		ActionsName.push_back(imgname[i]);
	}

	//count
	int stopFrame = 4;

	int moveFrame = 1;

	int attackLeftFrame = 1;

	int attackRightFrame = 1;

	int hurtFrame = 1;

	int dieFrame = 1;

	int frameanim[6] = { stopFrame, moveFrame, attackLeftFrame, attackRightFrame, hurtFrame, dieFrame };
	m_ActionsFrameCount.clear();
	for (int i = 0; i < 6; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}

	AddAnim(m_ShipName + imgname[0], frameanim[0], 0, callfunc_selector(Ship_Carrack::ShipStopStart), callfunc_selector(Ship_Carrack::ShipStopEnd));
	AddAnim(m_ShipName + imgname[1], frameanim[1], 0, callfunc_selector(Ship_Carrack::ShipMoveStart), callfunc_selector(Ship_Carrack::ShipMoveEnd));
	AddAnim(m_ShipName + imgname[2], frameanim[2], 0, callfunc_selector(Ship_Carrack::ShipAttackLeftStart), callfunc_selector(Ship_Carrack::ShipAttackLeftEnd));
	AddAnim(m_ShipName + imgname[3], frameanim[3], 0, callfunc_selector(Ship_Carrack::ShipAttackRightStart), callfunc_selector(Ship_Carrack::ShipAttackRightEnd));
	AddAnim(m_ShipName + imgname[4], frameanim[4], 0, callfunc_selector(Ship_Carrack::ShipHurtStart), callfunc_selector(Ship_Carrack::ShipHurtEnd));
	AddAnim(m_ShipName + imgname[5], frameanim[5], 0, callfunc_selector(Ship_Carrack::ShipDieStart), callfunc_selector(Ship_Carrack::ShipDieEnd));

	InitSprite(m_ShipName + imgname[0]);

	//
	mLeftEmitter = new BulletEmitter(this);
	mRightEmitter = new BulletEmitter(this);

}


Ship_Carrack::~Ship_Carrack()
{
	if (mLeftEmitter) delete mLeftEmitter;
	if (mRightEmitter) delete mRightEmitter;

}
//-----------------------------------------------------
void Ship_Carrack::InitShip()
{
	ShipBase::InitShip();

	//SetResource(m_ShipName);
	//
	InitData();

	m_SelfBoundBoxSize.width = 16.0f;
	m_SelfBoundBoxSize.height = 32.0f;
}
//-----------------------------------------------------
void Ship_Carrack::ShipStopStart()
{

}

void Ship_Carrack::ShipStopUpdate(float dt)
{

}

void Ship_Carrack::ShipStopEnd()
{

}
//-----------------------------------------------------
void Ship_Carrack::ShipMoveStart()
{

}

void Ship_Carrack::ShipMoveUpdate(float dt)
{

}

void Ship_Carrack::ShipMoveEnd()
{

}
//-----------------------------------------------------
void Ship_Carrack::ShipAttackRightStart()
{

}

void Ship_Carrack::ShipAttackRightUpdate(float dt)
{

}

void Ship_Carrack::ShipAttackRightEnd()
{

}
//-----------------------------------------------------
void Ship_Carrack::ShipAttackLeftStart()
{

}

void Ship_Carrack::ShipAttackLeftUpdate(float dt)
{

}

void Ship_Carrack::ShipAttackLeftEnd()
{

}
//-----------------------------------------------------
void Ship_Carrack::ShipHurtStart()
{

}

void Ship_Carrack::ShipHurtUpdate(float dt)
{

}

void Ship_Carrack::ShipHurtEnd()
{

}

//-----------------------------------------------------

void Ship_Carrack::ShipDieStart()
{

}

void Ship_Carrack::ShipDieUpdate(float dt)
{

}

void Ship_Carrack::ShipDieEnd()
{

}
//-----------------------------------------------------
void Ship_Carrack::Move()
{

}

void Ship_Carrack::Stop()
{

}

void Ship_Carrack::TurnLeft()
{

}

void Ship_Carrack::TurnRight()
{

}

void Ship_Carrack::AttackLeft()
{

}

void Ship_Carrack::AttackRight()
{

}

void Ship_Carrack::EatItem( /*ItemType tItem*/)
{

}

void Ship_Carrack::ShipBattleCtrl(ShipCtrlType t, ShipCtrlEvent evt)
{
	if (t == ShipCtrlType_Move)
	{
		if (evt == KeyPressed) Steering()->BoostOn();
		if (evt == KeyReleased) Steering()->BoostOff();

		PlayAnim(m_ShipName+"Move");
	}

	if (t == ShipCtrlType_Break)
	{
		if (evt == KeyPressed) Steering()->BreakDownOn();
		if (evt == KeyReleased) Steering()->BreakDownOff();

		PlayAnim(m_ShipName + "Stop");
	}

	if (t ==  ShipCtrlType_TurnLeft)
	{
		if (evt == KeyPressed) Steering()->TurnLeftOn();
		if (evt == KeyReleased) Steering()->TurnLeftOff();
	}

	
	if (t == ShipCtrlType_TurnRight)
	{
		if (evt == KeyPressed) Steering()->TurnRightOn();
		if (evt == KeyReleased) Steering()->TurnRightOff();
	}

	if (t == ShipCtrlType_FireLeft)
	{
		if (evt == KeyPressed) mLeftEmitter->Shot(BulletEmitter::face_left);
	}

	if (t == ShipCtrlType_FireRight)
	{
		if (evt == KeyPressed) mLeftEmitter->Shot(BulletEmitter::face_right);
	}

}

void Ship_Carrack::InitData()
{
	Vehicle::InitData();
}

void Ship_Carrack::UpdateShip(float delta)
{
	ShipBase::UpdateShip(delta);

	Tick(delta);

	LeftEmitter()->TickEmitter(delta);
	RightEmitter()->TickEmitter(delta);

	cocos2d::Rect oldBoundingBox = this->getBoundingBox();
	//cocos2d::Rect newBoundingBox = cocos2d::Rect(cocos2d::Vec2(mPos.x, mPos.y), oldBoundingBox.size);
	cocos2d::Rect newBoundingBox = cocos2d::Rect(cocos2d::Vec2(mPos.x - m_SelfBoundBoxSize.width*0.5f, mPos.y - m_SelfBoundBoxSize.height*0.5f), m_SelfBoundBoxSize);
	//
	//if (BattleMapManager::getInstance()->IsCollideMapObstacle(newBoundingBox) == false)
	/*
	if (!BattleMapManager::getInstance()->IsCollideIntersect(newBoundingBox))
>>>>>>> .r20
	{
		setPosition(mPos.x, mPos.y);
	}
<<<<<<< .mine
	
	if (BattleMapManager::getInstance()->IsCollideNavalBase(this))
	{
	}

	if (BattleMapManager::getInstance()->IsCollideNavalFlag(this))
	{
	}
	
	=======
	*/
	setPosition(mPos.x, mPos.y);
	//
	//CCLOG("%f,%f", mPos.x, mPos.y);

	//
	float angle = acos(mHeading.dot(cocos2d::Vec2::UNIT_Y));

	setRotation(angle * Drive::Sign(mHeading, cocos2d::Vec2::UNIT_Y) * 57.2974f);

}
