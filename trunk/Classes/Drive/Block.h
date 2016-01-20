/********************************************************************
	created:	2016/01/19
	created:	19:1:2016   13:10
	filename: 	E:\Armada\Classes\Drive\Block.h
	file path:	E:\Armada\Classes\Drive
	file base:	Block
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef Block_h__
#define Block_h__
///
#include "cocos2d.h"
#include <vector>

class Wall
{
public:
	Wall(	const cocos2d::Vec2& A,
			const cocos2d::Vec2& B,
			const cocos2d::Vec2& N = cocos2d::Vec2::ZERO):
			mA(A), mB(B)
	{
		if (N.isZero())
		{
			mN = (mB - mA).getNormalized().getRPerp();
		}
	}

	cocos2d::Vec2 Center()const{ return (mA + mB) * 0.5f; }
	cocos2d::Vec2 A()const{ return mA; }
	cocos2d::Vec2 B()const{ return mB; }
	cocos2d::Vec2 N()const{ return mN; }
	//
	float DistToLineSegment(const cocos2d::Vec2& P) const;
	float DistToLineSegmentSq(const cocos2d::Vec2& P) const;
	bool LineSegmentCircleIntersection(const cocos2d::Vec2& C, float radius) const;

	//
	static float DistToLineSegment(const cocos2d::Vec2& A, const cocos2d::Vec2& B,
		const cocos2d::Vec2& P);
	static float DistToLineSegmentSq(const cocos2d::Vec2& A, const cocos2d::Vec2& B,
		const cocos2d::Vec2& P);
	static bool LineSegmentCircleIntersection(const cocos2d::Vec2& A, const		cocos2d::Vec2& B, const cocos2d::Vec2& C, float radius);

protected:
	cocos2d::Vec2 mA;
	cocos2d::Vec2 mB;
	cocos2d::Vec2 mN;
	//
public:
	bool operator==(const Wall& rhs)const
	{
		return (mA.equals(rhs.mA) && mB.equals(rhs.mB) && mN.equals(rhs.mN));
	}
};
class Block
{
public:
	Block(const cocos2d::Rect& rect,bool CreateWalls = false);
	~Block();
	//
	void CalculateWalls();
	void SetRect(const cocos2d::Rect& rect, bool CreateWalls = false);

	bool IsCollision (const cocos2d::Rect& rect) const;
	bool IsCollision (float r, const cocos2d::Vec2& c)const ;

	const std::vector<Wall>& GetWalls() const { return mWalls; }
	const cocos2d::Rect& GetRect(){ return mRect; }
	//
	bool operator==(const Block& rhs)const
	{
		return mRect.equals(rhs.mRect);
	}
protected:
	std::vector<Wall>	mWalls;
	cocos2d::Rect		mRect;
private:
};


#endif // Block_h__
