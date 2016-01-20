#include "Block.h"
//////////////////////////////////////////////////////////////////////////
float Wall::DistToLineSegment(const cocos2d::Vec2& A, const cocos2d::Vec2& B, const cocos2d::Vec2& P)
{
	float dotA = (P.x - A.x)*(B.x - A.x) + (P.y - A.y)*(B.y - A.y);

	if (dotA <= 0) return A.distance(P);

	double dotB = (P.x - B.x)*(A.x - B.x) + (P.y - B.y)*(A.y - B.y);

	if (dotB <= 0) return B.distance(P);

	cocos2d::Vec2 Point = A + ((B - A) * dotA) / (dotA + dotB);

	return P.distance(Point);
}

float Wall::DistToLineSegment(const cocos2d::Vec2& P) const
{
	return DistToLineSegment(mA, mB, P);
}

float Wall::DistToLineSegmentSq(const cocos2d::Vec2& A, const cocos2d::Vec2& B, const cocos2d::Vec2& P)
{
	float dotA = (P.x - A.x)*(B.x - A.x) + (P.y - A.y)*(B.y - A.y);

	if (dotA <= 0) return A.distanceSquared(P);

	double dotB = (P.x - B.x)*(A.x - B.x) + (P.y - B.y)*(A.y - B.y);

	if (dotB <= 0) return B.distanceSquared(P);

	cocos2d::Vec2 Point = A + ((B - A) * dotA) / (dotA + dotB);

	return P.distanceSquared(Point);
}

float Wall::DistToLineSegmentSq(const cocos2d::Vec2& P) const
{
	return DistToLineSegmentSq(mA, mB, P);
}

bool Wall::LineSegmentCircleIntersection(const cocos2d::Vec2& A, const cocos2d::Vec2& B, const cocos2d::Vec2& C, float radius)
{
	float DistToLineSq = DistToLineSegmentSq(A, B, C);

	if (DistToLineSq < radius*radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Wall::LineSegmentCircleIntersection(const cocos2d::Vec2& C, float radius) const
{
	return LineSegmentCircleIntersection(mA, mB, C, radius);
}


//////////////////////////////////////////////////////////////////////////
Block::Block(const cocos2d::Rect& rect, bool CreateWalls)
{
	SetRect(rect, CreateWalls);
	mWalls.reserve(4);
}

Block::~Block()
{

}

void Block::CalculateWalls()
{
	const cocos2d::Rect& rect = mRect;
	cocos2d::Vec2  vMin = cocos2d::Vec2(rect.getMinX(), rect.getMinY());
	cocos2d::Vec2  vMax = cocos2d::Vec2(rect.getMaxX(), rect.getMaxY());
	float w = rect.size.width;
	float h = rect.size.height;
	//
	cocos2d::Vec2  p0 = vMin;
	cocos2d::Vec2  p1 = vMin + cocos2d::Vec2(w, 0);
	cocos2d::Vec2  p2 = vMax;
	cocos2d::Vec2  p3 = vMax - cocos2d::Vec2(w, 0);
	//
	mWalls.push_back(Wall(p0, p1));
	mWalls.push_back(Wall(p1, p2));
	mWalls.push_back(Wall(p2, p3));
	mWalls.push_back(Wall(p3, p0));


}

void Block::SetRect(const cocos2d::Rect& rect, bool CreateWalls /*= false*/)
{
	mRect = rect;
	if(CreateWalls)	CalculateWalls();
}

bool Block::IsCollision(const cocos2d::Rect& rect) const
{
	return mRect.intersectsRect(rect);
}

bool Block::IsCollision(float r, const cocos2d::Vec2& c) const
{
	return mRect.intersectsCircle(c, r);
}


