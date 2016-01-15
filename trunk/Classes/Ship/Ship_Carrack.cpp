#include "Ship_Carrack.h"


Ship_Carrack::Ship_Carrack()
{
	//name
	m_ShipName = "Ship_Carrack";
	//name
	std::string imgname[6] = { "Stop", "Move", "Attackleft", "Attackright", "Hurt", "Die" };
	//ActionsName = test; 
	for (int i = 0; i < 6; ++i)
	{
		ActionsName.push_back(imgname[i]);
	}

	//count
	int stopFrame = 1;

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
}


Ship_Carrack::~Ship_Carrack()
{
}
//-----------------------------------------------------
void Ship_Carrack::InitShip()
{
	SetResource(m_ShipName);
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
