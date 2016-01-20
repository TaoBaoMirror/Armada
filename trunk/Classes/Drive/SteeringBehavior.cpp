#include "SteeringBehavior.h"
#include "Vehicle.h"
#include "math.h"
#include "Block.h"
#include "World.h"

SteeringBehavior::SteeringBehavior(Vehicle* agent) :mVehicle(agent)
{
	mDeceleration = normal;
	mSteeringForce = cocos2d::Vec2::ZERO;
	mTarget = cocos2d::Vec2::ZERO;
	mFlags = none;
	//
	BlockAvoidanceOn();
}

SteeringBehavior::~SteeringBehavior()
{

}

cocos2d::Vec2 SteeringBehavior::Calculate()
{
	cocos2d::Vec2 force = cocos2d::Vec2::ZERO;

	mSteeringForce = cocos2d::Vec2::ZERO;

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

	if (On(turn_left))
	{
		force = TurnLeft();

		if (!AccumulateForce(mSteeringForce, force)) return mSteeringForce;
	}

	if (On(block_avoidance))
	{
		if (BlockAvoidance())
		{

		}
	}

	if (On(turn_right))
	{
		force = TurnRight();

		if (!AccumulateForce(mSteeringForce, force)) return mSteeringForce;
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

void SteeringBehavior::AddSteeringForce(const cocos2d::Vec2& force)
{
	mSteeringForce += force;
	//
	if (mVehicle->MaxForce() - mSteeringForce.length() <= 0)
	{
		mSteeringForce = mSteeringForce.getNormalized() * mVehicle->MaxForce();
	}
}

cocos2d::Vec2 SteeringBehavior::Boost()
{
	const float MaxBoost = 80;

	return mVehicle->Heading() * MaxBoost;
	
}

cocos2d::Vec2 SteeringBehavior::TurnLeft()
{
	const float SpeedToForceRate = 0.8f;

	float speed = mVehicle->Speed();

	if (speed < 0.01f) speed = 0.01f;

	return mVehicle->Side() * speed * SpeedToForceRate * -1;

}

cocos2d::Vec2 SteeringBehavior::TurnRight()
{
	const float SpeedToForceRate = 0.8f;

	float speed = mVehicle->Speed();

	if (speed < 0.01f) speed = 0.01f;

	return mVehicle->Side() * speed * SpeedToForceRate;
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
