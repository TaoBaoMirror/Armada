#include "GameManager.h"
#include "BattleMap\BattleMapManager.h"
#include "GameScene\BattleScene.h"

//---------------------------------------------------------
GameManager* GameManager::m_Instance = nullptr;

GameManager* GameManager::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameManager();
	}

	return m_Instance;
}
//---------------------------------------------------------
GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::EnterBattleMap(int num)
{
	if (BattleMapManager::getInstance()->LoadBattleMap(num) == true)
	{
		cocos2d::Director::getInstance()->replaceScene(BattleScene::createScene());
	}
	else
	{

	}
}
