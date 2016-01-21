/********************************************************************
	created:	2016/01/18
	created:	18:1:2016   14:41
	filename: 	E:\Armada\Classes\Bullet\BulletEmitter.h
	file path:	E:\Armada\Classes\Bullet
	file base:	BulletEmitter
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef BulletEmitter_h__
#define BulletEmitter_h__

#include "cocos2d.h"
#include "Ship/ShipBase.h"

class BulletEmitter
{
public:
	enum ShotType
	{
		face_left,face_right
	};

	enum BulletStyle
	{
		normal_Bullet
	};
public:
	BulletEmitter(ShipBase* ship);
	~BulletEmitter();
	//
	void		TickEmitter(float);
	void		SetMaxColdDown(float cd){ mColdDownTimer = cd; }
	float		MaxColdDown(){ return mMaxColdDown; }
	void		SetColdDownTimer(float cd){ mColdDownTimer = cd; }
	float		ColdDownTimer(){ return mColdDownTimer; }
	void		Shot(ShotType t);
	//
	void		SetBulletStyle(BulletStyle bs){ mBulletStyle = bs; }
	BulletStyle	GetBulletStyle(){ return mBulletStyle; }

	ShipBase*	GetShip(){ return mShip; }
protected:
	ShipBase*	mShip;
	//
	float	mColdDownTimer;
	float	mMaxColdDown;
	BulletStyle	mBulletStyle;
private:
};

#endif // BulletEmitter_h__
