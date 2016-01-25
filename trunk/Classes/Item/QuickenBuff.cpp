#include "QuickenBuff.h"
#include "Ship/ShipBase.h"

QuickenBuff::QuickenBuff() :Buff()
{

}

QuickenBuff::~QuickenBuff()
{

}

void QuickenBuff::Init()
{
	mEnable = true;
	//
	SetMaxDuringTime(4);
}

void QuickenBuff::OnAttachShip()
{
	Buff::OnAttachShip();
	//
	if (Bearer())
	{
		ShipBase* ship = (ShipBase*)Bearer();
		mSavedMaxSpeed = ship->MaxSpeed();
		mBuffMaxSpeed = mSavedMaxSpeed * 2;
		ship->SetMaxSpeed(mBuffMaxSpeed);
	}
}

void QuickenBuff::UpdateBuff(float dt)
{
	Buff::UpdateBuff(dt);
}

void QuickenBuff::OnDetachShip()
{
	if (Bearer())
	{
		ShipBase* ship = (ShipBase*)Bearer();
		ship->SetMaxSpeed(mSavedMaxSpeed);
	}

	Buff::OnDetachShip();
}
