/********************************************************************
	created:	2016/01/17
	created:	17:1:2016   10:06
	filename: 	E:\Armada\Classes\Drive\Vehicle.h
	file path:	E:\Armada\Classes\Drive
	file base:	Vehicle
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Vehicle_h__
#define Vehicle_h__
#include "cocos2d.h"
#include "Drive.h"
class SteeringBehavior;

class Vehicle : public Drive
{
public:
	Vehicle();
	~Vehicle();
	//
	void Tick(float);

	//
	double					TimeElapsed()const{ return mTimeElapsed; }
	cocos2d::Vec2			SmoothedHeading()const{ return mSmoothedHeading; }
	SteeringBehavior*const  Steering()const{ return mSteering; }
	void*const				World()const{ return mWorld; }
protected:
	//
	void*				mWorld;
	//
	SteeringBehavior*	mSteering;
	cocos2d::Vec2		mSmoothedHeading;
	float				mTimeElapsed;
	//
	Vehicle(const Vehicle&);
	Vehicle& operator=(const Vehicle&);
	//
	void WrapAround(cocos2d::Vec2 &pos, int MaxX, int MaxY);
private:
};

#endif // Vehicle_h__
