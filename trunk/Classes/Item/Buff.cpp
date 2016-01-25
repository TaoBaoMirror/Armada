#include "Buff.h"

Buff::Buff() : 
mEnable(false), 
mProvider(nullptr), 
mBearer(nullptr),
mDuringTime(0.01f),
mMaxDuringTime(0.01f)
{

}

Buff::~Buff()
{

}

void Buff::Init()
{
	
}

void Buff::OnAttachShip()
{
	if (!mEnable) return;
	//
	mDuringTime = mMaxDuringTime;
}

void Buff::UpdateBuff(float dt)
{
	if (!mEnable) return;
	//
	mDuringTime -= dt;
	//
	if (mDuringTime <= 0)
	{
		mEnable = false;
		return;
	}
}

void Buff::OnDetachShip()
{

}
