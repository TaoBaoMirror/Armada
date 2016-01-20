#include "BattleMapManager.h"
#include "BattleMap.h"
#include "Drive/World.h"

BattleMapManager* BattleMapManager::m_Instance = nullptr;

BattleMapManager* BattleMapManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new BattleMapManager();
	}

	return m_Instance;
}

//----------------------------------------

BattleMapManager::BattleMapManager() :
m_CurBattleMap(nullptr),
m_NavalBase(nullptr),
m_bTeamBornEdge(BornEdgeType::BornEdgeType_Left)
{
}


BattleMapManager::~BattleMapManager()
{
}

BattleMap* BattleMapManager::GetBattleMap()
{
	return m_CurBattleMap;
}

bool BattleMapManager::LoadBattleMap(int num)
{
	if (m_CurBattleMap != nullptr)
	{
		delete m_CurBattleMap;
		m_CurBattleMap = nullptr;
	}

	m_CurBattleMap = new BattleMap();

	//string mappath = "Map" + num;
	bool ret = m_CurBattleMap->InitBattleMap("map\\testBattleMap.tmx");

	return ret;
}

void BattleMapManager::ReleaseBattleMap()
{
	if (m_CurBattleMap != nullptr)
	{
		delete m_CurBattleMap;
		m_CurBattleMap = nullptr;
	}
}

void BattleMapManager::SetTeamBornEdge(BornEdgeType edge)
{
	m_bTeamBornEdge = edge;
}

BornEdgeType BattleMapManager::GetTeamBornEdge()
{
	return m_bTeamBornEdge;
}

void BattleMapManager::AddMapCollision(MapCollision* mc)
{
	m_MapCollisions.push_back(mc);
	//--TEST
	World::GetInstance()->AddBlock(mc->GetRect(),true);
}

void BattleMapManager::RemoveMapCollision(MapCollision* mc)
{
	std::vector<MapCollision*>::iterator it = m_MapCollisions.begin();
	for (; it != m_MapCollisions.end(); ++it)
	{
		if (*it == mc)
		{
			m_MapCollisions.erase(it);
			break;
		}
	}
}

bool BattleMapManager::IsCollideMapObstacle(cocos2d::Rect& rec)
{
	std::vector<MapCollision*>::iterator it = m_MapCollisions.begin();
	for (; it != m_MapCollisions.end(); ++it)
	{
		MapCollision* mc = *it;
		if (mc != nullptr)
		{
			if (mc->IsCollision(rec) == true)
			{
				return true;
			}
		}
	}

	return false;
}

bool BattleMapManager::IsCollideNavalBase(ShipBase* pShip)
{
	if (m_NavalBase->CheckCollideShip(pShip) == true)
	{
		return true;
	}

	return false;
}

bool BattleMapManager::IsCollideNavalFlag(ShipBase* pShip)
{
	std::map<BornEdgeType, NavalFlagBase*>::iterator it = m_NavalFlagBases.begin();
	for (; it != m_NavalFlagBases.end(); ++it)
	{
		NavalFlagBase* pFlagbase = it->second;
		if (pFlagbase->CheckCollideShip(pShip))
		{
			return true;
		}
	}
	return false;
}

void BattleMapManager::SetNavalBase(NavalBase* naval)
{
	m_NavalBase = naval;
}

NavalBase* BattleMapManager::GetNavalBase()
{
	return m_NavalBase;
}

void BattleMapManager::SetNavalFlagBase(BornEdgeType type, NavalFlagBase* pFlagBase)
{
	m_NavalFlagBases[type] = pFlagBase;
}

NavalFlagBase* BattleMapManager::GetNavalFlagBase(BornEdgeType type)
{
	std::map<BornEdgeType, NavalFlagBase*>::iterator it = m_NavalFlagBases.find(type);
	if (it != m_NavalFlagBases.end())
	{
		return it->second;
	}

	return nullptr;
}

void BattleMapManager::SetNavalPort(BornEdgeType type, NavalPort* pPort)
{
	m_NavalPorts[type] = pPort;
}

NavalPort* BattleMapManager::GetNavalPort(BornEdgeType type)
{
	std::map<BornEdgeType, NavalPort*>::iterator it = m_NavalPorts.find(type);
	if (it != m_NavalPorts.end())
	{
		return it->second;
	}

	return nullptr;
}





