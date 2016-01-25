/********************************************************************
	created:	2016/01/23
	created:	23:1:2016   16:11
	filename: 	E:\Armada\Classes\Item\BuffCreater.h
	file path:	E:\Armada\Classes\Item
	file base:	BuffCreater
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef BuffCreater_h__
#define BuffCreater_h__

class Buff;
class BuffCreater
{
public:
	static Buff*	CreateBuff(int buffType);
protected:
	BuffCreater();
	~BuffCreater();
private:
};
#endif // BuffCreater_h__
