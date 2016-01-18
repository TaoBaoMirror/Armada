/********************************************************************
	created:	2016/01/17
	created:	17:1:2016   10:11
	filename: 	E:\Armada\Classes\Drive\SteeringBehavior.h
	file path:	E:\Armada\Classes\Drive
	file base:	SteeringBehavior
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef SteeringBehavior_h__
#define SteeringBehavior_h__

#include "cocos2d.h"

class Vehicle;

//--------------------------- Constants ----------------------------------


//
class SteeringBehavior
{
public:
	enum Deceleration{ slow = 3, normal = 2, fast = 1 };

public:
	SteeringBehavior(Vehicle* agent);
	virtual ~SteeringBehavior();
	//
	cocos2d::Vec2 Calculate();
	//
	void SetTarget(const cocos2d::Vec2& t);
	void SetDeceleration(Deceleration d){ mDeceleration = d; }
	//

	//计算平行于头部的驱动力
	float    ForwardComponent();

	//计算垂直于头部的驱动力
	float    SideComponent();
	//

protected:
	//
	Vehicle*		mVehicle;
	//驱动力
	cocos2d::Vec2   mSteeringForce;
	//
	cocos2d::Vec2   mTarget;
	//
	Deceleration	mDeceleration;
	//
	bool      AccumulateForce(cocos2d::Vec2 &sf, const cocos2d::Vec2& ForceToAdd);
	cocos2d::Vec2 Arrive(const cocos2d::Vec2& TargetPos, Deceleration deceleration);

private:

};

#endif // SteeringBehavior_h__
