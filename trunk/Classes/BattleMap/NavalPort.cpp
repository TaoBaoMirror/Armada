#include "NavalPort.h"

//-------------------------------------------------

NavalPort::NavalPort(BornEdgeType type) :
m_BornPos(cocos2d::Vec2::ZERO)
{
	m_bBelongToType = type;
}


NavalPort::~NavalPort()
{
}

void NavalPort::Update(float dt)
{
	std::map<TeamShipSeat, ReadyBorn*>::iterator it = m_ReadyBornShips.begin();
	for (; it != m_ReadyBornShips.end(); ++it)
	{
		ReadyBorn* pReadyBorn = it->second;
		if (pReadyBorn->IsReadyBorn() == true)
		{
			pReadyBorn->Update(dt);

			if (pReadyBorn->CanBorn())
			{
				pReadyBorn->Born(m_BornPos);
			}
		}
	}
}

BornEdgeType NavalPort::GetBelongType()
{
	return m_bBelongToType;
}

void NavalPort::InitNavalPort(cocos2d::Vec2 centerPos)
{
	m_BornPos = centerPos;
}

void NavalPort::AddReadyBorn(TeamShipSeat seat)
{
	ReadyBorn* pReadyBorn = new ReadyBorn(m_bBelongToType, seat);
	m_ReadyBornShips[seat] = pReadyBorn;
}

void NavalPort::ReadyBornShip(TeamShipSeat seat)
{
	std::map<TeamShipSeat, ReadyBorn*>::iterator it = m_ReadyBornShips.find(seat);
	if (it != m_ReadyBornShips.end())
	{
		ReadyBorn* pReadyBorn = it->second;
		if (pReadyBorn != nullptr)
		{
			pReadyBorn->EnableReadyBorn();
		}
	}
}

void NavalPort::BornShipDirect(TeamShipSeat seat)
{
	std::map<TeamShipSeat, ReadyBorn*>::iterator it = m_ReadyBornShips.find(seat);
	if (it != m_ReadyBornShips.end())
	{
		ReadyBorn* pReadyBorn = it->second;
		if (pReadyBorn != nullptr)
		{
			pReadyBorn->Born(m_BornPos);
		}
	}
}
