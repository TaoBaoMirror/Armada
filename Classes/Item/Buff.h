/********************************************************************
	created:	2016/01/23
	created:	23:1:2016   15:51
	filename: 	E:\Armada\Classes\Item\Buff.h
	file path:	E:\Armada\Classes\Item
	file base:	Buff
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Buff_h__
#define Buff_h__

class Buff
{
public:
	Buff();
	virtual ~Buff();
	//
	virtual void Init();
	//
	void	SetMaxDuringTime(float d){ mMaxDuringTime = d; }
	float	DuringTime(){ return mDuringTime; }
	void	SetProvider(void* provider){ mProvider = provider; }
	void*	Provider(){ return mProvider; }

	void	SetBearer(void* bearer){ mBearer = bearer; }
	void*	Bearer(){ return mBearer; }

	void	BuffOn(){ mEnable = true; }
	bool	IsEnable(){ return mEnable; }
	//
	virtual void OnAttachShip();
	virtual void UpdateBuff(float dt);
	virtual void OnDetachShip();
	//
protected:
	float	mDuringTime;
	float	mMaxDuringTime;
	void*	mProvider;
	void*	mBearer;
	bool	mEnable;
private:
};
#endif // Buff_h__
