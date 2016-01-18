#include "Vehicle.h"
#include "SteeringBehavior.h"

Vehicle::Vehicle(void* world)
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

	if (hasResistance)
	{
		SteeringForce = mSteering->Resistance();
	}
	//���ٶ�
	cocos2d::Vec2 acceleration = SteeringForce / mMass;
	//�����ٶ�
	mVelocity += acceleration * time_elapsed;
	//����������ٶ�
	if (mVelocity.length() > mMaxSpeed)
	{
		mVelocity.normalize();

		mVelocity.scale(mMaxSpeed);
	}

	//����λ��
	mPos += mVelocity * time_elapsed;

	//����ٶȲ�Ϊ0������ͷ��
	if (mVelocity.lengthSquared() > 0.00001f)
	{
		SetHeading(mVelocity.getNormalized());
	}

	//��ס�߽�
	//WrapAround(mPos, mWorld->cxClient(), mWorld->cyClient());

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
}
