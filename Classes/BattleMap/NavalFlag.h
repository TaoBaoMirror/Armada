#ifndef __NAVAL_FLAG_H__
#define __NAVAL_FLAG_H__

#include "cocos2d.h"
#include "GameScene\BattleSceneCommon.h"
#include "Ship\ShipBase.h"

class NavalFlag : public cocos2d::Sprite
{
public:
	NavalFlag(BornEdgeType type);
	~NavalFlag();

	void InitRes();

	void SetEnableFlag();

	void SetDisableFlag();

	bool IsEnableFlag();

	bool IsCatchFlag(ShipBase* pShip);

	BornEdgeType GetBelongTo();

protected:
	BornEdgeType m_bBelongToType;

	bool m_bIsEnable;
};

#endif //__NAVAL_FLAG_H__