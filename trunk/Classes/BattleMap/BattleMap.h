#ifndef ChunkMap_h__
#define ChunkMap_h__

#include "cocos2d.h"

class BattleMap : public cocos2d::TMXTiledMap
{
public:
	BattleMap();
	~BattleMap();

	bool	InitBattleMap(std::string tmxFile);

	cocos2d::TMXLayer* GetCreatureTMXLayer();
	cocos2d::Layer* GetShipLayer();
	cocos2d::Layer* GetEffectLayer();
	cocos2d::Layer* GetItemLayer();

	cocos2d::Vec2 GetTeamBornPoint();
	cocos2d::Vec2 GetEnemyBornPoint();

	void update(float delta) override;

	void onEnter() override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

protected:
	cocos2d::Vec2 m_TeamBornPoint;

	cocos2d::Vec2 m_EnemyBornPoint;
};

#endif