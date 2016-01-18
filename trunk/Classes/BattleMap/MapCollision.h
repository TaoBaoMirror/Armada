#ifndef __MAP_COLLISION_H__
#define __MAP_COLLISION_H__

#include "cocos2d.h"

class MapCollision
{
public:
	MapCollision(cocos2d::Sprite* sp);
	~MapCollision();

	void SetRect(cocos2d::Rect rec);

	bool IsCollision(const cocos2d::Rect otherRect);

	void SetCanBreak();
	bool CanBreak();

	void Break();

protected:
	cocos2d::Rect m_BoundRect;

	bool m_bCanBreak;

	cocos2d::Sprite* m_Sprite;
};

#endif

