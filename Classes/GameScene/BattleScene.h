#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "Ship\ShipManager.h"

enum BattleStatue
{
	BattleStatue_Ready = 0,
	BattleStatue_Fight,
	BattleStatue_Settlement,
};

class BulletBase;
class BattleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(BattleScene);

	virtual void update(float delta) override;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

	void onHoldPress_Forward();
	void onHoldPress_Left();
	void onHoldPress_Right();
	//
	void AddBullet(BulletBase* bullet);
	
protected:
	BattleStatue m_BTS;

	//void DeployTeamShip(TeamShipSeat seat);

	//void DeployEnemyShip(TeamShipSeat seat);

	void DeployShip(BornEdgeType type, TeamShipSeat seat);

	bool m_bHoldPress_Forward;
	bool m_bHoldPress_Left;
	bool m_bHoldPress_Right;
};

#endif
