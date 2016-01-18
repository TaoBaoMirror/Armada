#include "BattleMapManager.h"
#include "BattleMap.h"

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

bool BattleMapManager::IsCollideIntersect(cocos2d::Rect& rec)
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


