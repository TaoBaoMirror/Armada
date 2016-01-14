#include "BattleScene.h"
#include "BattleMap\BattleMap.h"
#include "BattleMap\BattleMapManager.h"
#include "Ship\ShipManager.h"

USING_NS_CC;

cocos2d::Scene* BattleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BattleScene::create();
	// add layer as a child to scene
	scene->addChild(layer,0);

	BattleMap* pBLayer = BattleMapManager::getInstance()->GetBattleMap();

	scene->addChild(pBLayer, 1);

	// return the scene
	return scene;
}

bool BattleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_BTS = BattleStatue::BattleStatue_Ready;	

	//test init ships	
	DeployTeamShip(TeamShipSeat::TeamShipSeat_1);

	DeployEnemyShip(EnemyShipSeat::EnemyShipSeat_1);

	return true;
}

void BattleScene::update(float delta)
{
	switch (m_BTS)
	{
	case BattleStatue::BattleStatue_Ready:
		break;
	case BattleStatue::BattleStatue_Fight:
	{
		//update ships
	}
		break;
	case BattleStatue::BattleStatue_Settlement:
		break;
	default:
		break;
	}	
	
}

void BattleScene::DeployTeamShip(TeamShipSeat seat)
{
	//get cur map
	BattleMap* curmap = BattleMapManager::getInstance()->GetBattleMap();

	ShipBase* pTeamShip_1 = ShipManager::getInstance()->BornTeamShip(seat);
	curmap->GetShipLayer()->addChild(pTeamShip_1, 10);

	pTeamShip_1->setPosition(curmap->GetTeamBornPoint());
}

void BattleScene::DeployEnemyShip(EnemyShipSeat seat)
{
	//get cur map
	BattleMap* curmap = BattleMapManager::getInstance()->GetBattleMap();

	ShipBase* pEnemyShip_1 = ShipManager::getInstance()->BornEnemyShip(seat);
	curmap->GetShipLayer()->addChild(pEnemyShip_1, 10);

	pEnemyShip_1->setPosition(curmap->GetEnemyBornPoint());
}

