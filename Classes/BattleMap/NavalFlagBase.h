#ifndef __NAVAL_FLAG_BASE_H__
#define __NAVAL_FLAG_BASE_H__

#include "cocos2d.h"
#include "Ship\ShipBase.h"
#include "GameScene\BattleSceneCommon.h"
#include "NavalFlag.h"

class NavalFlagBase
{
public:
	NavalFlagBase();
	~NavalFlagBase();

	void SetBelongToType(BornEdgeType type);
	BornEdgeType GetBelongType();

	void InitNabalFlagBase(cocos2d::Vec2 centerpos);

	bool CheckCollideShip(ShipBase* pShip);

	void CatchFlag();

	void RecoveryFlag();

	void SetFlagAt(cocos2d::Vec2 pos);

protected:

	BornEdgeType m_bBelongToType;

	NavalFlag* m_Flag;

	cocos2d::Vec2 m_OriFlagPos;
};

#endif //__NAVAL_FLAG_BASE_H__