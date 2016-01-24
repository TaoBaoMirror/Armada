#include "BattleScene.h"
#include "BattleMap\BattleMap.h"
#include "BattleMap\BattleMapManager.h"
#include "Ship\ShipManager.h"
#include "Bullet\BulletBase.h"
#include "Drive\World.h"
#include "Item\ItemManager.h"
#include "Item\Item.h"

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
	//DeployTeamShip(TeamShipSeat::TeamShipSeat_1);

	//DeployEnemyShip(TeamShipSeat::TeamShipSeat_1);

	DeployShip(BornEdgeType::BornEdgeType_Left, TeamShipSeat::TeamShipSeat_1);

	DeployShip(BornEdgeType::BornEdgeType_Right, TeamShipSeat::TeamShipSeat_1);

	ShipManager::getInstance()->SetSelfShipSeat(BornEdgeType::BornEdgeType_Left, TeamShipSeat::TeamShipSeat_1);
	//end

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
		//update emp
		Emplacement* pEmpLeft = BattleMapManager::getInstance()->GetEmplacement(BornEdgeType::BornEdgeType_Left);
		Emplacement* pEmpRight = BattleMapManager::getInstance()->GetEmplacement(BornEdgeType::BornEdgeType_Right);
		if (pEmpLeft != nullptr)
		{
			pEmpLeft->update(delta);
		}
		if (pEmpRight != nullptr)
		{
			pEmpRight->update(delta);
		}
		//update ships
		ShipManager::getInstance()->Update(delta);
		//
		World::GetInstance()->Tick(delta);
		//
		ItemManager::GetInstance()->UpdateItems(delta);
	}
		break;
	case BattleStatue::BattleStatue_Settlement:
		break;
	default:
		break;
	}	
	
}
//
//void BattleScene::DeployTeamShip(TeamShipSeat seat)
//{
//	//get cur map
//	BattleMap* curmap = BattleMapManager::getInstance()->GetBattleMap();
//
//	ShipBase* pTeamShip = ShipManager::getInstance()->BornTeamShip(seat);
//	curmap->GetShipLayer()->addChild(pTeamShip, 10);
//
//	if (BattleMapManager::getInstance()->GetTeamBornEdge() == BornEdgeType_Left)
//	{
//		//pTeamShip->setPosition(curmap->GetLeftBornPoint());
//		pTeamShip->SetPos(curmap->GetLeftBornPoint());
//	}
//	else
//	{
//		//pTeamShip->setPosition(curmap->GetRightBornPoint());
//		pTeamShip->SetPos(curmap->GetRightBornPoint());
//
//	}
//	
//	
//}
//
//void BattleScene::DeployEnemyShip(TeamShipSeat seat)
//{
//	//get cur map
//	BattleMap* curmap = BattleMapManager::getInstance()->GetBattleMap();
//
//	ShipBase* pEnemyShip = ShipManager::getInstance()->BornEnemyShip(seat);
//	curmap->GetShipLayer()->addChild(pEnemyShip, 10);
//	
//	if (BattleMapManager::getInstance()->GetTeamBornEdge() == BornEdgeType_Left)
//	{
//		//pEnemyShip->setPosition(curmap->GetRightBornPoint());	
//		pEnemyShip->SetPos(curmap->GetRightBornPoint());
//
//	}
//	else
//	{
//		//pEnemyShip->setPosition(curmap->GetLeftBornPoint());
//		pEnemyShip->SetPos(curmap->GetLeftBornPoint());
//
//	}
//}


void BattleScene::DeployShip(BornEdgeType type, TeamShipSeat seat)
{
	NavalPort* pPort = BattleMapManager::getInstance()->GetNavalPort(type);
	if (pPort != nullptr)
	{
		pPort->AddReadyBorn(seat);

		pPort->BornShipDirect(seat);
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

		///
		// TEST
		///
		if (keyCode == EventKeyboard::KeyCode::KEY_P)
		{
			RandomCreateItemInScene();
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

void BattleScene::AddBullet(BulletBase* bullet)
{
	cocos2d::Layer* bulletLayer = BattleMapManager::getInstance()->GetBattleMap()->GetBulletLayer();

	if (bulletLayer)
	{
		bulletLayer->addChild(bullet);
	}


}

void BattleScene::RandomCreateItemInScene()
{
	int  itemType = 1;

	Item* item = ItemManager::GetInstance()->CreateItem(itemType);

	cocos2d::Layer* itemLayer = BattleMapManager::getInstance()->GetBattleMap()->GetItemLayer();

	if (itemLayer)
	{
		itemLayer->addChild(item);
	}

	ItemManager::GetInstance()->AddItem(item);
	Size s_size = itemLayer->getBoundingBox().size;
	item->setPosition(RandomHelper::random_int(0, (int)s_size.width), RandomHelper::random_int(0, (int)s_size.height));
	item->setPosition(400, 200);

}

