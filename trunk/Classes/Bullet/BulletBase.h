/********************************************************************
	created:	2016/01/18
	created:	18:1:2016   14:40
	filename: 	E:\Armada\Classes\Bullet\BulletBase.h
	file path:	E:\Armada\Classes\Bullet
	file base:	BulletBase
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef BulletBase_h__
#define BulletBase_h__

#include "cocos2d.h"
#include "Drive/Vehicle.h"

class BulletEmitter;
class Block;
class BulletBase : public cocos2d::Sprite ,public Vehicle
{
public:
	BulletBase(BulletEmitter* emitter);
	virtual ~BulletBase();
	//Inherit from Vehicle
	virtual void Tick(float) override;
	virtual void InitData();
	//New here
	void Fly();


protected:

	float	mAttackDamage;
	float	mMaxAttackDamage;

	bool	mCollidedDestory;
	float	mSafeAliveTime;
	bool	mAlive;
	int		mCollideCounter;

	BulletEmitter*	mBirthEmitter;

	void	CollisionWorld();
	virtual void OnCollision(Drive* DynamicObjectCollider);
	virtual void OnCollision(Block* StaticObjectCollider);
	void	DestoryBullet();
private:

public:
	static bool IsCollision(BulletBase* bullet, Drive* DynamicObject);
	static bool IsCollision(BulletBase* bullet, Block* StaticObject);

};
#endif // BulletBase_h__
