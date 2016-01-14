#include "BattleMap.h"

#define ShipLayerTag 0xa1	//生物体数据层
#define ItemLayerTag 0xa3		//物品层
#define EffectLayerTag 0xa4		//特效层




BattleMap::BattleMap()
{
}


BattleMap::~BattleMap()
{
}

void BattleMap::update(float delta)
{

}

void BattleMap::onEnter()
{

}

void BattleMap::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{

}

void BattleMap::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{

}

bool BattleMap::InitBattleMap(std::string tmxFile)
{
	if (initWithTMXFile(tmxFile))
	{
		return true;
	}
	return false;
}
//--------------------------------------------------------------
cocos2d::TMXLayer* BattleMap::GetCreatureTMXLayer()
{
	return nullptr;
}

cocos2d::Layer* BattleMap::GetShipLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(ShipLayerTag));
}

cocos2d::Layer* BattleMap::GetEffectLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(EffectLayerTag));
}

cocos2d::Layer* BattleMap::GetItemLayer()
{
	return static_cast<cocos2d::Layer*>(this->getChildByTag(ItemLayerTag));
}

//---------------------------------------------------------------------------
cocos2d::Vec2 BattleMap::GetTeamBornPoint()
{
	return m_TeamBornPoint;
}

cocos2d::Vec2 BattleMap::GetEnemyBornPoint()
{
	return m_EnemyBornPoint;
}
