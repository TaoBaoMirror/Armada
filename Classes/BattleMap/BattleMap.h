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
	cocos2d::Layer* GetBulletLayer();

	cocos2d::TMXLayer* GetBuildLayer();
	cocos2d::TMXLayer* GetLandLayer();

	cocos2d::Vec2 GetLeftBornPoint();
	cocos2d::Vec2 GetRightBornPoint();

	virtual void update(float delta) override;

	virtual void onEnter() override;
	virtual void onExit() override;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event);
	
protected:
	cocos2d::Vec2 m_LeftBornPoint;

	cocos2d::Vec2 m_RightBornPoint;
};

#endif