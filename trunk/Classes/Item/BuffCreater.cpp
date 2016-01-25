#include "BuffCreater.h"
#include "Buff.h"
#include "QuickenBuff.h"


Buff* BuffCreater::CreateBuff(int buffType)
{
	Buff* buff = nullptr;

	switch (buffType)
	{
	case 1:
		buff = new QuickenBuff();
		break;
	default:
		break;
	}
	//
	if (buff) buff->Init();	//??

	//
	return buff;
}
