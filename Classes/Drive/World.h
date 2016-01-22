/********************************************************************
	created:	2016/01/19
	created:	19:1:2016   13:11
	filename: 	E:\Armada\Classes\Drive\World.h
	file path:	E:\Armada\Classes\Drive
	file base:	World
	file ext:	h
	author:		wwh
	
	purpose:	
*********************************************************************/
#ifndef World_h__
#define World_h__

#include <vector>
#include "cocos2d.h"
#include "Block.h"

class Drive;
class BulletBase;
class World
{
public:
	static World* GetInstance();
	//
	void Init();
	void Tick(float);
	void Free();
	//
	void AddBlock(const cocos2d::Rect& rect, bool createWall = false);
	void RemoveBlock(const Block& block);
	void RemoveBlock(const std::vector<Block>::iterator& cur_it);


	void AddWall(const cocos2d::Vec2& A, const cocos2d::Vec2& B);
	void RemoveWall(const Wall& wall);
	void RemoveWall(const std::vector<Wall>::iterator& cur_it);
	//
	void AddDynamicObject(Drive* obj);
	void RemoveDynamicObject(Drive* obj);
	//
	void AddBullet(BulletBase*	bullet);
	void RemoveBullet(BulletBase*	bullet);

public:

	std::vector<Block>& GetBlocks(){ return mBlocks; }
	std::vector<bool>& GetBlocksActive(){ return mBlocksActive; }

	bool GetBlocksActive(const std::vector<Block>::iterator& cur_it)
	{
		return mBlocksActive[cur_it - mBlocks.begin()];
	}


	std::vector<Wall>& GetWalls(){ return mWalls; }
	std::vector<bool>& GetWallsActive(){ return mWallsActive; }

	bool GetBlocksActive(const std::vector<Wall>::iterator& cur_it)
	{
		return mWallsActive[cur_it - mWalls.begin()];
	}
	//
	//
	const std::vector<Drive*>& GetDynamicObjects(){ return mDynamicObjects; }
	//
	std::list<BulletBase*>&	GetBullets(){ return mBullets; }
protected:
	std::vector<Block>	mBlocks;
	std::vector<bool>	mBlocksActive;
	std::vector<Wall>	mWalls;
	std::vector<bool>	mWallsActive;
	//
	std::vector<Drive*>	mDynamicObjects;
	//
	std::list<BulletBase*>	mBullets;
private:
	World();
	~World();
};
#endif // World_h__
