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
	m_SelfShipSeat = TeamShipSeat_1;
}


ShipManager::~ShipManager()
{
}

//-----------------------------------------
void ShipManager::Update(float dt)
{
	std::map<TeamShipSeat, ShipBase*>::iterator itTeam = m_Team_Left_Ships.begin();
	for (; itTeam != m_Team_Left_Ships.end(); ++itTeam)
	{
		ShipBase* pShip = itTeam->second;
		if (pShip != nullptr)
		{
			pShip->UpdateShip(dt);
		}
	}

	std::map<TeamShipSeat, ShipBase*>::iterator itEnemy = m_Team_Right_Ships.begin();
	for (; itEnemy != m_Team_Right_Ships.end(); ++itEnemy)
	{
		ShipBase* pShip = itEnemy->second;
		if (pShip != nullptr)
		{
			pShip->UpdateShip(dt);
		}
	}
}
//-----------------------------------------
void ShipManager::SetSelfShipSeat(BornEdgeType borntype, TeamShipSeat seat)
{
	m_SelfBornEdgeType = borntype;

	m_SelfShipSeat = seat;
}

//
//ShipBase* ShipManager::BornTeamShip(TeamShipSeat index, ShipType type /*= ShipType::ShipType_Carrack*/)
//{
//	ShipBase* pNewShip = nullptr;
//
//	switch (type)
//	{
//	case ShipType_Carrack:
//	{
//							 pNewShip = new Ship_Carrack();
//	}
//		break;
//	default:
//		break;
//	}
//
//	if (pNewShip != nullptr)
//	{
//		pNewShip->InitShip();
//
//		std::map<TeamShipSeat, ShipBase*>::iterator it = m_TeamShips.find(index);
//		if (it == m_TeamShips.end())
//		{
//			m_TeamShips[index] = pNewShip;
//		}
//		else
//		{
//			it->second->removeFromParentAndCleanup(true);
//
//			delete it->second;
//
//			it->second = pNewShip;
//		}
//	}	
//
//	return pNewShip;
//}
//
//ShipBase* ShipManager::BornEnemyShip(TeamShipSeat index, ShipType type /*= ShipType::ShipType_Carrack*/)
//{
//	ShipBase* pNewShip = nullptr;
//
//	switch (type)
//	{
//	case ShipType_Carrack:
//	{
//							 pNewShip = new Ship_Carrack();
//	}
//		break;
//	default:
//		break;
//	}
//
//	if (pNewShip != nullptr)
//	{
//		pNewShip->InitShip();
//
//		std::map<TeamShipSeat, ShipBase*>::iterator it = m_EnemyShips.find(index);
//		if (it == m_EnemyShips.end())
//		{
//			m_EnemyShips[index] = pNewShip;
//		}
//		else
//		{
//			it->second->removeFromParentAndCleanup(true);
//
//			delete it->second;
//
//			it->second = pNewShip;
//		}
//	}
//
//	return pNewShip;
//}

ShipBase* ShipManager::BornShip(BornEdgeType borntype, TeamShipSeat index, ShipType type /*= ShipType::ShipType_Carrack*/)
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
		pNewShip->InitShip();

		if (borntype == BornEdgeType::BornEdgeType_Left)
		{
			std::map<TeamShipSeat, ShipBase*>::iterator it = m_Team_Left_Ships.find(index);
			if (it == m_Team_Left_Ships.end())
			{
				m_Team_Left_Ships[index] = pNewShip;
			}
			else
			{
				it->second->removeFromParentAndCleanup(true);

				delete it->second;

				it->second = pNewShip;
			}
		}
		else if (borntype == BornEdgeType::BornEdgeType_Right)
		{
			std::map<TeamShipSeat, ShipBase*>::iterator it = m_Team_Right_Ships.find(index);
			if (it == m_Team_Right_Ships.end())
			{
				m_Team_Right_Ships[index] = pNewShip;
			}
			else
			{
				it->second->removeFromParentAndCleanup(true);

				delete it->second;

				it->second = pNewShip;
			}
		}
		
	}

	return pNewShip;
}


void ShipManager::ClearAll()
{

}
//-----------------------------------------------------------
//ShipBase* ShipManager::GetTeamShip(TeamShipSeat num)
//{
//	std::map<TeamShipSeat, ShipBase*>::iterator it = m_TeamShips.find(num);
//	if (it == m_TeamShips.end())
//	{
//		return nullptr;
//	}
//
//	return it->second;
//}
//
//ShipBase* ShipManager::GetEnemyShip(TeamShipSeat num)
//{
//	std::map<TeamShipSeat, ShipBase*>::iterator it = m_EnemyShips.find(num);
//	if (it == m_EnemyShips.end())
//	{
//		return nullptr;
//	}
//
//	return it->second;
//}

ShipBase* ShipManager::GetShip(BornEdgeType borntype, TeamShipSeat num)
{
	if (borntype == BornEdgeType::BornEdgeType_Left)
	{
		std::map<TeamShipSeat, ShipBase*>::iterator it = m_Team_Left_Ships.find(num);
		if (it != m_Team_Left_Ships.end())
		{
			return it->second; 
		}		
	}
	else if (borntype == BornEdgeType::BornEdgeType_Right)
	{
		std::map<TeamShipSeat, ShipBase*>::iterator it = m_Team_Right_Ships.find(num);
		if (it != m_Team_Right_Ships.end())
		{
			return it->second;
		}
	}

	return nullptr;
}


ShipBase* ShipManager::GetSelfShip()
{
	if (m_SelfBornEdgeType == BornEdgeType::BornEdgeType_Left)
	{
		std::map<TeamShipSeat, ShipBase*>::iterator it = m_Team_Left_Ships.find(m_SelfShipSeat);
		if (it != m_Team_Left_Ships.end())
		{
			return it->second;
		}		
	}
	else if (m_SelfBornEdgeType == BornEdgeType::BornEdgeType_Right)
	{
		std::map<TeamShipSeat, ShipBase*>::iterator it = m_Team_Right_Ships.find(m_SelfShipSeat);
		if (it != m_Team_Right_Ships.end())
		{
			return it->second;
		}
	}

	return nullptr;
	
}

ShipBase* ShipManager::FindShipByDistance(BornEdgeType borntype, cocos2d::Vec2 oriPos, float dis)
{
	switch (borntype)
	{
	case BornEdgeType_Left:
	{
							  std::map<TeamShipSeat, ShipBase*>::iterator itTeam = m_Team_Left_Ships.begin();
							  for (; itTeam != m_Team_Left_Ships.end(); ++itTeam)
							  {
								  ShipBase* pShip = itTeam->second;
								  if (pShip != nullptr)
								  {
									  cocos2d::Vec2 shippos = pShip->getPosition();
									  if (shippos.distance(oriPos) < dis)
									  {
										  return pShip;
									  }
								  }
							  }
	}
		break;
	case BornEdgeType_Right:
	{
							   std::map<TeamShipSeat, ShipBase*>::iterator itTeam = m_Team_Right_Ships.begin();
							   for (; itTeam != m_Team_Right_Ships.end(); ++itTeam)
							   {
								   ShipBase* pShip = itTeam->second;
								   if (pShip != nullptr)
								   {
									   cocos2d::Vec2 shippos = pShip->getPosition();
									   if (shippos.distance(oriPos) < dis)
									   {
										   return pShip;
									   }
								   }
							   }
	}
		break;
	default:
		break;
	}
	//
	return nullptr;
}
