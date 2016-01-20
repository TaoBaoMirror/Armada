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
	//
	//
	auto label = Label::createWithTTF("DebugInfo", "fonts/Marker Felt.ttf", 24);
	label->setColor(cocos2d::Color3B::RED);
	label->setPosition(label->getContentSize().width * 0.5f,
		cocos2d::Director::getInstance()->getWinSize().height - label->getContentSize().height* 0.5f);

	scene->addChild(label, 2, "DebugLable");

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
	BattleMapManager::getInstance()->SetTeamBornEdge(BornEdgeType::BornEdgeType_Left);

	DeployTeamShip(TeamShipSeat::TeamShipSeat_1);

	DeployEnemyShip(EnemyShipSeat::EnemyShipSeat_1);

	setKeyboardEnabled(true);

	scheduleUpdate();

	m_bHoldPress_Forward = false;
	m_bHoldPress_Left = false;
	m_bHoldPress_Right = false;

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
		if (m_bHoldPress_Forward)
		{
			onHoldPress_Forward();
		}
		if (m_bHoldPress_Left)
		{
			onHoldPress_Left();
		}
		if (m_bHoldPress_Right)
		{
			onHoldPress_Right();
		}
		//update ships
		ShipManager::getInstance()->Update(delta);
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

	ShipBase* pTeamShip = ShipManager::getInstance()->BornTeamShip(seat);
	curmap->GetShipLayer()->addChild(pTeamShip, 10);

	if (BattleMapManager::getInstance()->GetTeamBornEdge() == BornEdgeType_Left)
	{
		//pTeamShip->setPosition(curmap->GetLeftBornPoint());
		pTeamShip->SetPos(curmap->GetLeftBornPoint());
	}
	else
	{
		//pTeamShip->setPosition(curmap->GetRightBornPoint());
		pTeamShip->SetPos(curmap->GetRightBornPoint());

	}
	
	
}

void BattleScene::DeployEnemyShip(EnemyShipSeat seat)
{
	//get cur map
	BattleMap* curmap = BattleMapManager::getInstance()->GetBattleMap();

	ShipBase* pEnemyShip = ShipManager::getInstance()->BornEnemyShip(seat);
	curmap->GetShipLayer()->addChild(pEnemyShip, 10);
	
	if (BattleMapManager::getInstance()->GetTeamBornEdge() == BornEdgeType_Left)
	{
		//pEnemyShip->setPosition(curmap->GetRightBornPoint());	
		pEnemyShip->SetPos(curmap->GetRightBornPoint());

	}
	else
	{
		//pEnemyShip->setPosition(curmap->GetLeftBornPoint());
		pEnemyShip->SetPos(curmap->GetLeftBornPoint());

	}
}

void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	if (m_BTS == BattleStatue::BattleStatue_Ready)
	{
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			m_BTS = BattleStatue::BattleStatue_Fight;
		}
	}
	if (m_BTS == BattleStatue::BattleStatue_Fight)
	{
		ShipBase* pShip = ShipManager::getInstance()->GetSelfShip();


		//Move
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			m_bHoldPress_Forward = true;

			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_Move, ShipCtrlEvent::KeyPressed);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_Break, ShipCtrlEvent::KeyPressed);
		}
		//Turn
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			m_bHoldPress_Left = true;

			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_TurnLeft, ShipCtrlEvent::KeyPressed);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			m_bHoldPress_Right = true;

			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_TurnRight, ShipCtrlEvent::KeyPressed);
		}

		//Attack
		if (keyCode == EventKeyboard::KeyCode::KEY_G)
		{
			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_FireLeft, ShipCtrlEvent::KeyPressed);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_H)
		{
			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_FireRight, ShipCtrlEvent::KeyPressed);
		}


	}
	else if (m_BTS == BattleStatue::BattleStatue_Settlement)
	{
	}
}

void BattleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (m_BTS == BattleStatue::BattleStatue_Fight)
	{
		ShipBase* pShip = ShipManager::getInstance()->GetSelfShip();
		//Move
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			m_bHoldPress_Forward = false;

			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_Move, ShipCtrlEvent::KeyReleased);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_Break, ShipCtrlEvent::KeyReleased);
		}

		//Turn
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			m_bHoldPress_Left = false;

			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_TurnLeft, ShipCtrlEvent::KeyReleased);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{
			m_bHoldPress_Right = false;

			pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_TurnRight, ShipCtrlEvent::KeyReleased);
		}
		
		if (!m_bHoldPress_Left && !m_bHoldPress_Right)
		{
			pShip->Pin();
		}
	}
}

void BattleScene::onHoldPress_Forward()
{
	ShipBase* pShip = ShipManager::getInstance()->GetSelfShip();

	pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_Move, ShipCtrlEvent::KeyDown);
}

void BattleScene::onHoldPress_Left()
{
	ShipBase* pShip = ShipManager::getInstance()->GetSelfShip();

	pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_TurnLeft, ShipCtrlEvent::KeyDown);
}

void BattleScene::onHoldPress_Right()
{
	ShipBase* pShip = ShipManager::getInstance()->GetSelfShip();

	pShip->ShipBattleCtrl(ShipCtrlType::ShipCtrlType_TurnRight, ShipCtrlEvent::KeyDown);
}

