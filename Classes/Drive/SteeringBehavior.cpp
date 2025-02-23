#include "SteeringBehavior.h"
#include "Vehicle.h"
#include "math.h"
#include "Block.h"
#include "World.h"

SteeringBehavior::SteeringBehavior(Vehicle* agent) :mVehicle(agent), mMaxTorque(6.28f), mMaxBoost(80)
{
	mDeceleration = normal;
	mSteeringForce = cocos2d::Vec2::ZERO;
	mTarget = cocos2d::Vec2::ZERO;
	mFlags = none;
	//
	//BlockAvoidanceOn();
}

SteeringBehavior::~SteeringBehavior()
{

}

cocos2d::Vec2 SteeringBehavior::Calculate()
{
	cocos2d::Vec2 force = cocos2d::Vec2::ZERO;

	mTorque = 0;

	mSteeringForce = cocos2d::Vec2::ZERO;

	//将前进和转向拆开了
	if (On(turn_left))
	{
		mTorque += TurnLeft();
	}

	if (On(turn_right))
	{
		mTorque += TurnRight();
	}

	if (On(arrive))
	{
		force = Arrive(mTarget, mDeceleration) * 1;
		//
		if (!AccumulateForce(mSteeringForce, force)) return mSteeringForce;
	}

	
	if (On(boost))
	{
		force = Boost();

		if (!AccumulateForce(mSteeringForce, force)) return mSteeringForce;
	}

	if (On(breakdown))
	{
		force = BreakDown();

		if (!AccumulateForce(mSteeringForce, force)) return mSteeringForce;
	}

	if (On(block_avoidance))
	{
		if (BlockAvoidance())
		{

		}
	}



	return mSteeringForce;
}

float SteeringBehavior::ForwardComponent()
{
	return mVehicle->Heading().dot(mSteeringForce);
}

float SteeringBehavior::SideComponent()
{
	return mVehicle->Side().dot(mSteeringForce);
}

bool SteeringBehavior::AccumulateForce(cocos2d::Vec2 &RunningTot, const cocos2d::Vec2& ForceToAdd)
{
	//目前所承受的驱动力的情况
	float MagnitudeSoFar = RunningTot.length();

	//还剩余多少驱动力
	float MagnitudeRemaining = mVehicle->MaxForce() - MagnitudeSoFar;

	//不能承受更多的力了
	if (MagnitudeRemaining <= 0.0) return false;

	//计算增加的驱动力长度
	float MagnitudeToAdd = ForceToAdd.length();

	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot += ForceToAdd;
	}

	else
	{
		RunningTot += (ForceToAdd.getNormalized() * MagnitudeRemaining);
	}

	return true;
}

cocos2d::Vec2 SteeringBehavior::Arrive(const cocos2d::Vec2& TargetPos, Deceleration deceleration)
{
	cocos2d::Vec2 ToTarget = TargetPos - mVehicle->Pos();

	float dist = ToTarget.length();

	if (dist > 0.0001f)
	{
		const float DecelerationTweaker = 0.3f;

		float speed = dist / ((float)deceleration * DecelerationTweaker);

		speed = fmin(speed, mVehicle->MaxSpeed());

		cocos2d::Vec2 DesiredVelocity = ToTarget * speed / dist;

		return (DesiredVelocity - mVehicle->Velocity());
	}

	return cocos2d::Vec2(0, 0);
}

void SteeringBehavior::SetTarget(const cocos2d::Vec2& t)
{
	mTarget = t;
}

cocos2d::Vec2 SteeringBehavior::Boost()
{

	return mVehicle->Heading() * mMaxBoost;
	
}

float SteeringBehavior::TurnLeft()
{

	return mMaxTorque * counter_clockwise;

}

float SteeringBehavior::TurnRight()
{

	return mMaxTorque * clockwise;
}

cocos2d::Vec2 SteeringBehavior::BreakDown()
{
	if (mVehicle->SpeedSq() >= 0.00001f)
	{
		float speed = mVehicle->Speed();

		if (speed < 0.001f) speed = 0;

		return mVehicle->Heading() * speed * -0.8f;
	}

	return cocos2d::Vec2::ZERO;
}

bool SteeringBehavior::BlockAvoidance()
{
	const std::vector<Block>& blocks = mVehicle->GetWorld()->GetBlocks();
	std::vector<Block>::const_iterator it = blocks.begin();

	for (; it != blocks.end();++it)
	{
		bool col = it->IsCollision(mVehicle->Radius(), mVehicle->Pos());
		//
		if (col)
		{
			/*
			const std::vector<Wall>& walls = it->GetWalls();
			std::vector<Wall>::const_iterator w_it = walls.begin();

			for (; w_it != walls.end();++w_it)
			{
				if (w_it->LineSegmentCircleIntersection(mVehicle->Pos(), mVehicle->Radius()))
				{
					cocos2d::Vec2& I = mVehicle->Velocity();
					cocos2d::Vec2& N = w_it->N();
					cocos2d::Vec2 refVec = I - 2 * I.dot(N) * N;
					mSteeringForce = refVec.getNormalized() * 80;
					mVehicle->SetVelocity(cocos2d::Vec2::ZERO);
					return true;

				}
			}
			*/
			mVehicle->SetVelocity(cocos2d::Vec2::ZERO);
			mSteeringForce = cocos2d::Vec2::ZERO;
			return true;
		}
	}

	return false;
}
