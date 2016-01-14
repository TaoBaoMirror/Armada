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
m_CurBattleMap(nullptr)
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


