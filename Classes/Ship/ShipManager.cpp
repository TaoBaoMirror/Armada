#include "ShipManager.h"
#include "Ship_Carrack.h"

ShipManager* ShipManager::m_Instance = nullptr;

ShipManager* ShipManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new ShipManager();
	}

	return m_Instance;
}
//-----------------------------------------

ShipManager::ShipManager()
{
}


ShipManager::~ShipManager()
{
}

void ShipManager::SetSelfShipSeat(TeamShipSeat seat)
{
	m_SelfShipSeat = seat;
}


ShipBase* ShipManager::BornTeamShip(TeamShipSeat index, ShipType type /*= ShipType::ShipType_Carrack*/)
{
	ShipBase* pNewShip = nullptr;

	switch (type)
	{
	case ShipType_Carrack:
	{
							 pNewShip = new Ship_Carrack();
	}
		break;
	default:
		break;
	}

	if (pNewShip != nullptr)
	{
		std::map<TeamShipSeat, ShipBase*>::iterator it = m_TeamShips.find(index);
		if (it == m_TeamShips.end())
		{
			m_TeamShips[index] = pNewShip;
		}
		else
		{
			it->second->removeFromParentAndCleanup(true);

			delete it->second;
			it->second = pNewShip;
		}
	}	

	return pNewShip;
}

ShipBase* ShipManager::BornEnemyShip(EnemyShipSeat index, ShipType type /*= ShipType::ShipType_Carrack*/)
{
	ShipBase* pNewShip = nullptr;

	switch (type)
	{
	case ShipType_Carrack:
	{
							 pNewShip = new Ship_Carrack();
	}
		break;
	default:
		break;
	}

	std::map<EnemyShipSeat, ShipBase*>::iterator it = m_EnemyShips.find(index);
	if (it == m_EnemyShips.end())
	{
		m_EnemyShips[index] = pNewShip;
	}
	else
	{
		it->second->removeFromParentAndCleanup(true);

		delete it->second;
		it->second = pNewShip;
	}

	return pNewShip;
}

void ShipManager::ClearAll()
{

}
//-----------------------------------------------------------
ShipBase* ShipManager::GetTeamShip(TeamShipSeat num)
{
	std::map<TeamShipSeat, ShipBase*>::iterator it = m_TeamShips.find(num);
	if (it == m_TeamShips.end())
	{
		return nullptr;
	}

	return it->second;
}

ShipBase* ShipManager::GetEnemyShip(EnemyShipSeat num)
{
	std::map<EnemyShipSeat, ShipBase*>::iterator it = m_EnemyShips.find(num);
	if (it == m_EnemyShips.end())
	{
		return nullptr;
	}

	return it->second;
}

ShipBase* ShipManager::GetSelfShip()
{
	std::map<TeamShipSeat, ShipBase*>::iterator it = m_TeamShips.find(m_SelfShipSeat);
	if (it == m_TeamShips.end())
	{
		return nullptr;
	}

	return it->second;
}
