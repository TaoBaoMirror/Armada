#include "SteeringBehavior.h"
#include "Vehicle.h"
#include "math.h"

SteeringBehavior::SteeringBehavior(Vehicle* agent)
{

}

SteeringBehavior::~SteeringBehavior()
{

}

cocos2d::Vec2 SteeringBehavior::Calculate()
{
	mSteeringForce += Arrive(mTarget, mDeceleration) * 1;
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
	//Ŀǰ�����ܵ������������
	float MagnitudeSoFar = RunningTot.length();

	//��ʣ�����������
	float MagnitudeRemaining = mVehicle->MaxForce() - MagnitudeSoFar;

	//���ܳ��ܸ��������
	if (MagnitudeRemaining <= 0.0) return false;

	//�������ӵ�����������
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

	if (dist > 0)
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
