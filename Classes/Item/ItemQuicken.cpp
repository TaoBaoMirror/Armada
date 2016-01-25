#include "ItemQuicken.h"


ItemQuicken::ItemQuicken():
Item(8, FLT_MAX, 1)
{
	//test
	bool ret = Sprite::initWithFile("item/quickenItem.png");
}

ItemQuicken::~ItemQuicken()
{

}
