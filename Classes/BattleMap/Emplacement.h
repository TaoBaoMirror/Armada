#ifndef __EMPLACEMENT_H__
#define __EMPLACEMENT_H__

#include "cocos2d.h"
#include "Common\GameAnimation.h"
#include "Ship\ShipBase.h"

class Emplacement : public GameAnimation
{
public:
	Emplacement();
	~Emplacement();

	virtual void update(float dt) override;

protected:
	ShipBase* FindAndAimEnemyShip();

	void AttackEnemyShip();

	bool IsAttackCoolDownOver();

	bool m_bIsCoolDownOver;

	float m_CoolDownTime;
	float m_CurCoolDownTime;
};

#endif //__EMPLACEMENT_H__