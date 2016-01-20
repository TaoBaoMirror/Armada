#ifndef __NAVAL_PORT_H__
#define __NAVAL_PORT_H__

#include "cocos2d.h"
#include "GameScene\BattleSceneCommon.h"
#include "Ship\ShipBase.h"
#include "Ship\ShipManager.h"
#include "ReadyBornShip.h"

class NavalPort
{
public:
	NavalPort(BornEdgeType type);
	~NavalPort();

	void Update(float dt);

	void SetBelongToType(BornEdgeType type);
	BornEdgeType GetBelongType();

	void InitNavalPort(cocos2d::Vec2 centerPos);
	void AddReadyBorn(TeamShipSeat seat);

	void ReadyBornShip(TeamShipSeat seat);

	void BornShipDirect(TeamShipSeat seat);

protected:
	BornEdgeType m_bBelongToType;

	std::map<TeamShipSeat, ReadyBorn*> m_ReadyBornShips;

	cocos2d::Vec2 m_BornPos;
};

#endif//__NAVAL_PORT_H__