#include "BulletEmitter.h"
#include "Ship/ShipBase.h"
#include "BulletBase.h"
#include "Drive/World.h"

BulletEmitter::BulletEmitter(Vehicle* ship) :
mBulletStyle(normal_Bullet), mShip(ship)
{
	mMaxColdDown = 1;
	mColdDownTimer = mMaxColdDown;
	mDefaultDir = cocos2d::Vec2::ZERO;
	mDefaultPos = cocos2d::Vec2::ZERO;
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
		const cocos2d::Vec2& dir = GetVehicle()->Side() * -1;

		bullet->SetPos(GetVehicle()->Pos());
		bullet->SetVelocity(dir * bullet->MaxSpeed());
		
	}
	else if (t == face_right)
	{
		const cocos2d::Vec2& dir = GetVehicle()->Side();

		bullet->SetPos(GetVehicle()->Pos());
		bullet->SetVelocity(dir * bullet->MaxSpeed());
	}
	else if (t == custom_dir)
	{	
		bullet->SetPos(mDefaultPos);
		bullet->SetVelocity(mDefaultDir * bullet->MaxSpeed());
	}

	if (bullet)
	{
		bullet->Fly();
		mColdDownTimer = mMaxColdDown;
	}
	//

}

