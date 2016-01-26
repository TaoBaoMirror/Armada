#include "TitleScene.h"
#include "GameManager\GameManager.h"
#include "ResDef.h"
#include "BattleMap\BattleMapManager.h"
#include "BattleSceneCommon.h"
#include "Network\MatchVSDemoScence.h"

USING_NS_CC;

cocos2d::Scene* TitleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TitleScene::create();
	// add layer as a child to scene
	scene->addChild(layer, 0);

	// return the scene
	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	return true;
}

void TitleScene::onEnter()
{
	//////////////////////////////
	// 1. super init first

	Layer::onEnter();

	scheduleUpdate();
	//
	//if (bFinishLoad == false && bLoading == false)
	{
		//bLoading = true;
		//std::thread loadThread(loadRes);
		//std::thread loadThread(std::bind( &LogoUI::loadRes, this));
		//ResDef::getInstance()->loadRes();
		//m_loadThread = new std::thread(&LogoUI::loadRes, this);

		loadRes();
		//m_loadThread->join();
	}

	//Test
	CCDirector::sharedDirector()->replaceScene(MatchVSDemoScence::createScene());
	//end
	//
	//Test
	//BattleMapManager::getInstance()->SetTeamBornEdge(BornEdgeType::BornEdgeType_Left);
	//GameManager::getInstance()->EnterBattleMap(0);
	//end
}

void TitleScene::loadRes()
{
	//LevelManager::Instance()->FillInfo();
	ResDef::getInstance()->loadRes();
	//ResDef::getInstance()->initRes(pLogoProgressBar->CurrentProgress);
	//pLogoProgressBar->setVisible(false);
	//bunkerLoadingBarFrame->setVisible(false);
	//
	//GoToLogoUI();
}