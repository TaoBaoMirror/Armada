#ifndef __BATTLEMAP_MANAGER_H__
#define __BATTLEMAP_MANAGER_H__

#include "MapCollision.h"

class BattleMap;

enum BornEdgeType
{
	BornEdgeType_Left = 0,
	BornEdgeType_Right,
};

class BattleMapManager
{
public:	
	~BattleMapManager();

	static BattleMapManager* getInstance();

	BattleMap* GetBattleMap();

	bool LoadBattleMap(int num);

	void ReleaseBattleMap();

	void SetTeamBornEdge(BornEdgeType edge);

	BornEdgeType GetTeamBornEdge();

	void AddMapCollision(MapCollision* mc);
	void RemoveMapCollision(MapCollision* mc);

	bool IsCollideIntersect(cocos2d::Rect& rec);

protected:
	BattleMapManager();
	
	static BattleMapManager* m_Instance;

	BattleMap* m_CurBattleMap;

	BornEdgeType m_bTeamBornEdge;

	std::vector<MapCollision*> m_MapCollisions;
};

#endif//__BATTLEMAP_MANAGER_H__
