/********************************************************************
	created:	2016/01/23
	created:	23:1:2016   15:30
	filename: 	E:\Armada\Classes\Item\Item.h
	file path:	E:\Armada\Classes\Item
	file base:	Item
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Item_h__
#define Item_h__
#include "Common/GameAnimation.h"

class ShipBase;
class Item:public GameAnimation
{
public:
	Item(float r,float aliveTime,int buff);
	virtual ~Item();
	//
	bool OnCollision(ShipBase*	ship);
	//
	virtual void UpdateItem(float dt);
	virtual void DestoryItem();
	//
	bool Alive(){ return mAlive; }
protected:
	float mRadius;
	float mAliveTime;
	int	  mBuffType;
	bool  mAlive;
private:
};
#endif // Item_h__
