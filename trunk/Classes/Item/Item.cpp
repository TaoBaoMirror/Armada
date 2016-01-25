#include "Item.h"
#include "Buff.h"
#include "BuffCreater.h"
#include "Ship/ShipBase.h"

Item::Item(float r, float aliveTime, int buff) :
mRadius(r),
mAlive(true),
mBuffType(buff),
mAliveTime(FLT_MAX)
{

}

Item::~Item()
{

}

bool Item::OnCollision(ShipBase* ship)
{
	if (!mAlive) return false;

	if (ship)
	{
		if (ship->CollideCircle(mRadius,getPosition()))
		{
			Buff*	buff = BuffCreater::CreateBuff(mBuffType);

			if (buff != nullptr)
			{
				ship->AddBuff(buff);
				return true;
			}
		}
	}
	return false;
}

void Item::UpdateItem(float dt)
{
	if (!mAlive) return;
	//
	mAliveTime -= dt;
	//
	if (mAliveTime<=0)
	{
		DestoryItem();
	}
	//
}

void Item::DestoryItem()
{
	mAlive = false;

	removeFromParentAndCleanup(true);
}
