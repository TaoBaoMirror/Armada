#ifndef __EMPLACEMENT_H__
#define __EMPLACEMENT_H__

#include "cocos2d.h"
#include "Common\GameAnimation.h"
#include "Ship\ShipBase.h"
#include "Bullet\BulletEmitter.h"

class Emplacement : public GameAnimation
{
public:
	Emplacement(BornEdgeType edgetype);
	~Emplacement();

	virtual void update(float dt) override;

protected:
	void FindTargetShip();

	bool IsWithinRange();

	bool IsWithinDegree();

	void AttackTargetShip();

	void RotToTargetShip(float dt);

	bool IsAttackCoolDownOver();

	float m_Range;

	float m_CurDegree;

	float m_DegreeThreshold;

	float m_DegreeSpeed;

	BornEdgeType m_EdgeType;

	ShipBase* m_LockTarget;

	BulletEmitter*	mGunEmitter;
};

#endif //__EMPLACEMENT_H__