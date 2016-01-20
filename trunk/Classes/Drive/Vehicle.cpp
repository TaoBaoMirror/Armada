#include "Vehicle.h"
#include "SteeringBehavior.h"
#include "World.h"


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

	//���ٶ�
	cocos2d::Vec2 acceleration = SteeringForce / mMass;
	//�����ٶ�
	mVelocity += acceleration * time_elapsed;
	//
	if (hasResistance)
	{
		mVelocity *= 0.85f;
	}
	//����������ٶ�
	if (mVelocity.length() > mMaxSpeed)
	{
		mVelocity.normalize();

		mVelocity.scale(mMaxSpeed);
	}

	//����λ��
	auto mPosAdd = mVelocity * time_elapsed;
	mPos += mPosAdd;

	if (Steering()->BlockAvoidance())
	{
		mPos -= mPosAdd;
	}
	

	//����ٶȲ�Ϊ0������ͷ��
	if (mVelocity.lengthSquared() > 0.00001f)
	{
		SetHeading(mVelocity.getNormalized());
	}



	/*
	if (Steering()->isSpacePartitioningOn())
	{
		World()->CellSpace()->UpdateEntity(this, OldPos);
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
}
