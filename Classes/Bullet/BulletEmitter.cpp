#include "BulletEmitter.h"
#include "Ship/ShipBase.h"
#include "BulletBase.h"
#include "Drive/World.h"

BulletEmitter::BulletEmitter(ShipBase* ship):
mBulletStyle(normal_Bullet), mShip(ship)
{
	mMaxColdDown = 3;
	mColdDownTimer = mMaxColdDown;
}

BulletEmitter::~BulletEmitter()
{

}

void BulletEmitter::TickEmitter(float time_elapsed)
{

		mColdDownTimer -= time_elapsed;

		if (mColdDownTimer <= 0)
		{
			mColdDownTimer = 0;
		}
	

}

void BulletEmitter::Shot(ShotType t)
{
	if (mColdDownTimer != 0)	return;

	BulletBase*	bullet = nullptr;

	if (mBulletStyle == normal_Bullet)
	{
		bullet = new BulletBase(this);
		bullet->InitData();
		World::GetInstance()->AddBullet(bullet);
	}

	if (t == face_left)
	{
		const cocos2d::Vec2& dir = GetShip()->Side() * -1;

		bullet->SetPos(GetShip()->Pos());
		bullet->SetVelocity(dir * bullet->MaxSpeed());
		
	}
	else if (t == face_right)
	{
		const cocos2d::Vec2& dir = GetShip()->Side();

		bullet->SetPos(GetShip()->Pos());
		bullet->SetVelocity(dir * bullet->MaxSpeed());

	}

	if (bullet)
	{
		bullet->Fly();
		mColdDownTimer = mMaxColdDown;

	}
	//

}

