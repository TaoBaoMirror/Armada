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

class BattleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(BattleScene);

	virtual void update(float delta) override;
	
protected:
	BattleStatue m_BTS;

	void DeployTeamShip(TeamShipSeat seat);

	void DeployEnemyShip(EnemyShipSeat seat);
};

#endif
