#include "BulletBase.h"
#include "Drive/World.h"
#include "Drive/SteeringBehavior.h"
#include "Drive/Vehicle.h"
#include "BulletEmitter.h"

BulletBase::BulletBase(BulletEmitter* emitter) :
	Vehicle(World::GetInstance()),mBirthEmitter(emitter),
	mNeedToDestory(false)
{

}

BulletBase::~BulletBase()
{

}

void BulletBase::Tick(float time_elapsed)
{
	mTimeElapsed = time_elapsed;

	if (!mAlive) return;

	mSafeAliveTime -= mTimeElapsed;

	if (mSafeAliveTime<0)
	{
		DestoryBullet();
		return;
	}
		
	if (mCollidedDestory && mCollideCounter>0)
	{
		DestoryBullet();
		return;
	}



	cocos2d::Vec2 OldPos = Pos();
	cocos2d::Vec2 SteeringForce = cocos2d::Vec2::ZERO;
	SteeringForce = mSteering->Calculate();
	//
	cocos2d::Vec2 acceleration = SteeringForce / mMass;
	//更新速度
	mVelocity += acceleration * time_elapsed;
	//不超过最大速度
	if (mVelocity.length() > mMaxSpeed)
	{
		mVelocity.normalize();

		mVelocity.scale(mMaxSpeed);
	}
	//
	auto mPosAdd = mVelocity * time_elapsed;
	mPos += mPosAdd;
	//
	CollisionWorld();
	//
	setPosition(mPos.x, mPos.y);
}

void BulletBase::InitData()
{
	Vehicle::InitData();
	//
	mAttackDamage = 10;
	mMaxAttackDamage = 10;
	mCollidedDestory = false;
	mSafeAliveTime = 2.2f;
	mAlive = false;
	mCollideCounter = 0;
	//
	initWithFile("bullet//bullet.png");
}
//////////////////////////////////////////////////////////////////////////
void BulletBase::CollisionWorld()
{
	const std::vector<Drive*>& Objs = GetWorld()->GetDynamicObjects();
	std::vector<Drive*>::const_iterator it = Objs.begin();
	for (; it != Objs.end();++it)
	{
		if (!mAlive) break;

		if (*it == mBirthEmitter->GetShip()) continue;

		if (BulletBase::IsCollision(this, *it))
		{
			OnCollision(*it);
			//
			mCollideCounter++;
		}
	}
	
	std::vector<Block>& Blocks = GetWorld()->GetBlocks();
	std::vector<Block>::iterator block_it = Blocks.begin();
	for (; block_it != Blocks.end(); ++block_it)
	{
		if (!mAlive) break;

		if (BulletBase::IsCollision(this, *block_it))
		{
			OnCollision(&*block_it);
			//
			mCollideCounter++;
		}
	}
	
}

void BulletBase::OnCollision(Drive* DynamicObjectCollider)
{
	CCLOG("Bullet DynamicObject");
}

void BulletBase::OnCollision(Block* StaticObjectCollider)
{
	CCLOG("Bullet Block");
	//
	DestoryBullet();

}
//////////////////////////////////////////////////////////////////////////
//
//			Static Func
//
//////////////////////////////////////////////////////////////////////////
bool BulletBase::IsCollision(BulletBase* bullet, Drive* DynamicObject)
{
	float r1 = bullet->Radius();
	const cocos2d::Vec2& pos1 = bullet->Pos();
	float r2 = DynamicObject->Radius();
	const cocos2d::Vec2& pos2 = DynamicObject->Pos();
	//
	return pos1.distanceSquared(pos2) < r1 * r2;

}

bool BulletBase::IsCollision(BulletBase* bullet, const Block& StaticObject)
{
	return StaticObject.IsCollision(bullet->Radius(), bullet->Pos());
}

void BulletBase::DestoryBullet()
{
	mAlive = false;

	mNeedToDestory = true;
}

void BulletBase::Fly()
{
	mAlive = true;
}

