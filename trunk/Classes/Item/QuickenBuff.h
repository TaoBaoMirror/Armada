/********************************************************************
	created:	2016/01/23
	created:	23:1:2016   16:26
	filename: 	E:\Armada\Classes\Item\QuickenBuff.h
	file path:	E:\Armada\Classes\Item
	file base:	QuickenBuff
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef QuickenBuff_h__
#define QuickenBuff_h__

#include "Buff.h"

class QuickenBuff:public Buff
{
public:
	QuickenBuff();
	~QuickenBuff();
	//
	virtual void Init() override;
	virtual void OnAttachShip() override;
	virtual void UpdateBuff(float dt) override;
	virtual void OnDetachShip() override;
	//
protected:
	float	mSavedMaxSpeed;
	float	mBuffMaxSpeed;
private:
};
#endif // QuickenBuff_h__
