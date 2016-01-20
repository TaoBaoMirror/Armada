#include "ReadyBornShip.h"
#include "BattleMap.h"
#include "BattleMapManager.h"


ReadyBorn::ReadyBorn(BornEdgeType edgeType, TeamShipSeat readyBornSeat) :
m_bIsReadyBorn(false),
m_bCanBorn(false),
m_EdgeType(edgeType),
m_ReadyBornSeat(readyBornSeat)
{
}


ReadyBorn::~ReadyBorn()
{
}

void ReadyBorn::Update(float dt)
{
	m_CurWaitTime -= dt;

	if (m_CurWaitTime >= 0.0f)
	{
		m_bIsReadyBorn = false;
		m_bCanBorn = true;
	}
}

void ReadyBorn::EnableReadyBorn()
{
	m_bIsReadyBorn = true;

	m_CurWaitTime = MaxWaitTime;
}

bool ReadyBorn::IsReadyBorn()
{
	return m_bIsReadyBorn;
}

bool ReadyBorn::CanBorn()
{
	return m_bCanBorn;
}

void ReadyBorn::Born(cocos2d::Vec2 pos)
{
	BattleMap* curmap = BattleMapManager::getInstance()->GetBattleMap();
	ShipBase* pEnemyShip = ShipManager::getInstance()->BornShip(m_EdgeType, m_ReadyBornSeat);
	curmap->GetShipLayer()->addChild(pEnemyShip, 10);

	pEnemyShip->SetPos(pos);

	m_bCanBorn = false;
	m_bIsReadyBorn = false;
}
