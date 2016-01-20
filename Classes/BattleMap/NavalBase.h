#ifndef __NAVAL_BASE_H__
#define __NAVAL_BASE_H__

#include "cocos2d.h"
#include "Ship\ShipBase.h"
#include "GameScene\BattleSceneCommon.h"

class NavalBase
{
public:
	NavalBase();
	~NavalBase();	

	void SetBelongToType(BornEdgeType type);
	BornEdgeType GetBelongType();

	void InitNabalBase(cocos2d::Vec2 pos, cocos2d::Size size);

	bool CheckCollideShip(ShipBase* pShip);

protected:

	cocos2d::Rect m_BaseBoundingBox;

	BornEdgeType m_bBelongToType;
};

#endif //__NAVAL_BASE_H__