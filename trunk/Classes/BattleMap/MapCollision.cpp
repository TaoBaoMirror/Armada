#include "MapCollision.h"


MapCollision::MapCollision(cocos2d::Sprite* sp) :
m_bCanBreak(false)
{
	m_Sprite = sp;
}


MapCollision::~MapCollision()
{
}

void MapCollision::SetRect(cocos2d::Rect rec)
{
	m_BoundRect = rec;
}

bool MapCollision::IsCollision(const cocos2d::Rect otherRect)
{
	if (m_BoundRect.intersectsRect(otherRect))
	{
		return true;
	}

	return false;
}

void MapCollision::SetCanBreak()
{
	m_bCanBreak = true;
}

bool MapCollision::CanBreak()
{
	return m_bCanBreak;
}

void MapCollision::Break()
{

}

cocos2d::Sprite* MapCollision::GetSprite()
{
	return m_Sprite;
}
