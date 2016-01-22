#include "World.h"
#include "Drive.h"
#include "Bullet/BulletBase.h"
World::World()
{
	Init();
}

World::~World()
{

}

World* World::GetInstance()
{
	static World W;
	return &W;
}

void World::Init()
{
	const int blockInitNum = 64;
	const int wallInitNum = 64;

	mBlocks.reserve(blockInitNum);	
	mWalls.reserve(wallInitNum);
	mBlocksActive.resize(blockInitNum, false);
	mWallsActive.resize(wallInitNum, false);


}

void World::Free()
{
	mBlocks.clear();
	mWalls.clear();
	//
	mBlocksActive.resize(mBlocksActive.size(), false);
	mWallsActive.resize(mWallsActive.size(), false);
}

void World::AddBlock(const cocos2d::Rect& rect,bool createWall)
{
	mBlocks.push_back(Block(rect, createWall));
	mBlocksActive[mBlocks.size() - 1] = true;
}

void World::RemoveBlock(const Block& block)
{
	int counter = 0;
	for each (Block  b in mBlocks)
	{
		if (b == block)
		{
			mBlocksActive[counter] = false;
		}

		counter++;
	}
}

void World::RemoveBlock(const std::vector<Block>::iterator& cur_it)
{
	mBlocksActive[cur_it - mBlocks.begin()] = false;
}

void World::AddWall(const cocos2d::Vec2& A, const cocos2d::Vec2& B)
{
	mWalls.push_back(Wall(A,B));
	mWallsActive[mWalls.size() - 1] = true;
}

void World::RemoveWall(const Wall& wall)
{
	int counter = 0;
	for each (Wall  w in mWalls)
	{
		if (w == wall)
		{
			mWallsActive[counter] = false;
		}

		counter++;
	}
}

void World::RemoveWall(const std::vector<Wall>::iterator& cur_it)
{
	mWallsActive[cur_it - mWalls.begin()] = false;
}

void World::AddDynamicObject(Drive* obj)
{
	mDynamicObjects.push_back(obj);

}

void World::RemoveDynamicObject(Drive* obj)
{
	int counter = 0;
	for each (Drive* d in mDynamicObjects)
	{
		if (d == obj)
		{
			break;
		}
		//
		counter++;
	}
	//
	if (mDynamicObjects.size()!=0)
	{
		mDynamicObjects.erase(mDynamicObjects.begin() + counter);
	}
}

void World::AddBullet(BulletBase* bullet)
{
	mBullets.push_back(bullet);
	//
	cocos2d::Director::getInstance()->getRunningScene()->addChild(bullet, 2);
}

void World::RemoveBullet(BulletBase* bullet)
{
	//mBullets.remove(bullet);
	//
	bullet->removeFromParentAndCleanup(true);
}

void World::Tick(float dt)
{
	std::list<BulletBase*>::iterator it = mBullets.begin();

	while (it != mBullets.end())
	{
		BulletBase* bullet = *it;
		bullet->Tick(dt);
		//
		if (bullet->NeedToDestory())
		{
			it = mBullets.erase(it);
			RemoveBullet(bullet);
			delete bullet;
		}
		else
		{
			it++;
		}
	}
}
