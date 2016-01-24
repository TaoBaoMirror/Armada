#include "Vehicle.h"
#include "SteeringBehavior.h"
#include "World.h"
//////////////////////////////////////////////////////////////////////////

/*常量*/

const cocos2d::Vec2 DefaultHeading = cocos2d::Vec2(0, 1);
const cocos2d::Vec2 DefaultSide = cocos2d::Vec2(1, 0);
const cocos2d::Vec2 DefaultVelocity = cocos2d::Vec2(0, 0);
const float DefaultMass = 1;
const float DefaultMaxSpeed = 100;
const float DefaultTurnRate = 30;
const float DefaultForce = 100;
const cocos2d::Vec2 DefaultShipPos = cocos2d::Vec2::ZERO;
const float DefaultRadius = 8;
//
const float DefaultAngularVelocity = 0;
const float DefaultmMaxAngularSpeed = 3.14f * 3;

Vehicle::Vehicle(World* world)
{
	mWorld = world;
	mTimeElapsed = 0.f;
	mSteering = new SteeringBehavior(this);
}

Vehicle::~Vehicle()
{
	delete mSteering;
}

void Vehicle::Tick(float time_elapsed)
{
	const bool hasResistance = false;
	mTimeElapsed = time_elapsed;
	cocos2d::Vec2 OldPos = Pos();
	cocos2d::Vec2 SteeringForce = cocos2d::Vec2::ZERO;
	SteeringForce = mSteering->Calculate();
	float Torque = mSteering->Torque();

	//加速度
	cocos2d::Vec2 acceleration = SteeringForce / mMass;
	float		  angular_acceleration = Torque / mMass;
	//更新速度
	mVelocity += acceleration * time_elapsed;
	mAngularVelocity += angular_acceleration * time_elapsed;
	//
	if (hasResistance)
	{
		mVelocity *= 0.85f;
	}
	//不超过最大速度
	if (mVelocity.length() > mMaxSpeed)
	{
		mVelocity.normalize();

		mVelocity.scale(mMaxSpeed);
	}

	if (abs(mAngularVelocity) > mMaxAngularSpeed)
	{
		mAngularVelocity = mAngularVelocity / abs(mAngularVelocity) * mMaxAngularSpeed;
	}
	//更新头部
	float angular = mAngularVelocity * time_elapsed;
	mHeading.rotate(cocos2d::Vec2::ZERO, angular);
	mSide = mHeading.getRPerp();
	//只需要驱动速度的大小累积值，方向是头部方向
	mVelocity = Heading() * Speed();
	//更新位置
	auto mPosAdd = mVelocity * time_elapsed;
	mPos += mPosAdd;

	if (Steering()->BlockAvoidance())
	{
		mPos -= mPosAdd;
	}



	//如果速度不为0，更新头部
	/*
	if (mVelocity.lengthSquared() > 0.00001f)
	{
		SetHeading(mVelocity.getNormalized());
	}
	*/
}

void Vehicle::WrapAround(cocos2d::Vec2 &pos, int MaxX, int MaxY)
{
	if (pos.x > MaxX) { pos.x = MaxX; }

	if (pos.x < 0)    { pos.x = 0; }

	if (pos.y < 0)    { pos.y = 0; }

	if (pos.y > MaxY) { pos.y = MaxY; }
}

void Vehicle::InitData()
{
	mHeading = DefaultHeading;
	mSide = DefaultSide;
	mVelocity = DefaultVelocity;
	mPos = DefaultShipPos;
	mMass = DefaultMass;
	mMaxForce = DefaultForce;
	mMaxSpeed = DefaultMaxSpeed;
	mMaxTurnRate = DefaultTurnRate;
	mRadius = DefaultRadius;
	//
	mAngularVelocity = DefaultAngularVelocity;
	mMaxAngularSpeed = DefaultmMaxAngularSpeed;

}
