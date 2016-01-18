/********************************************************************
	created:	2016/01/16
	created:	16:1:2016   9:37
	filename: 	E:\Armada\Classes\Drive\Drive.h
	file path:	E:\Armada\Classes\Drive
	file base:	Drive
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Drive_h__
#define Drive_h__

#include "cocos2d.h"
//////////////////////////////////////////////////////////////////////////

/*³£Á¿*/

const cocos2d::Vec2 DefaultHeading = cocos2d::Vec2(0, 1);
const cocos2d::Vec2 DefaultSide = cocos2d::Vec2(1, 0);
const cocos2d::Vec2 DefaultVelocity = cocos2d::Vec2(0, 0);
const float DefaultMass = 1;
const float DefaultMaxSpeed = 40;
const float DefaultTurnRate = 30;
const float DefaultForce = 40;
const cocos2d::Vec2 DefaultShipPos = cocos2d::Vec2::ZERO;



//////////////////////////////////////////////////////////////////////////
class Drive
{
public:
	Drive();
	virtual ~Drive();
	//
	cocos2d::Vec2	Pos()const{ return mPos; }
	void	SetPos(const cocos2d::Vec2& new_pos){ mPos = new_pos; }

	cocos2d::Vec2  Velocity()const{ return mVelocity; }
	void	SetVelocity(const cocos2d::Vec2& NewVel){ mVelocity = NewVel; }
	float	Mass()const{ return mMass; }

	cocos2d::Vec2  Side()const{ return mSide; }

	float   MaxSpeed()const{ return mMaxSpeed; }
	void	SetMaxSpeed(double new_speed){ mMaxSpeed = new_speed; }

	float	MaxForce()const{ return mMaxForce; }
	void	SetMaxForce(double mf){ mMaxForce = mf; }

	bool	IsSpeedMaxedOut()const{ return mMaxSpeed*mMaxSpeed >= mVelocity.lengthSquared(); }
	float	Speed()const{ return mVelocity.length(); }
	float	SpeedSq()const{ return mVelocity.lengthSquared(); }

	cocos2d::Vec2  Heading()const{ return mHeading; }
	void	SetHeading(const cocos2d::Vec2& new_heading);
	bool	RotateHeadingToFacePosition(const cocos2d::Vec2& target);

	float	MaxTurnRate()const{ return mMaxTurnRate; }
	void	SetMaxTurnRate(double val){ mMaxTurnRate = val; }
protected:
	cocos2d::Vec2	mPos;
	cocos2d::Vec2	mVelocity;
	cocos2d::Vec2	mHeading;
	cocos2d::Vec2	mSide;
	float			mMass;
	float			mMaxSpeed;
	float			mMaxForce;
	float			mMaxTurnRate;

private:
public:
	static int Sign(const cocos2d::Vec2& v1, const cocos2d::Vec2& v2);
};

#endif // Drive_h__
