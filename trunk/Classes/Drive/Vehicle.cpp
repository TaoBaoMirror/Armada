#include "Vehicle.h"
#include "SteeringBehavior.h"

Vehicle::Vehicle()
{
	mSteering = new SteeringBehavior(this);
}

Vehicle::~Vehicle()
{
	delete mSteering;
}

void Vehicle::Tick(float time_elapsed)
{
	mTimeElapsed = time_elapsed;
	cocos2d::Vec2 OldPos = Pos();
	cocos2d::Vec2 SteeringForce;
	SteeringForce = mSteering->Calculate();

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
		mHeading = mVelocity.getNormalized();

		mSide = mHeading.getRPerp();
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
