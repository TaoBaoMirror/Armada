#ifndef __BATTLEMAP_MANAGER_H__
#define __BATTLEMAP_MANAGER_H__

#include "MapCollision.h"
#include "GameScene\BattleSceneCommon.h"
#include "NavalBase.h"
#include "NavalFlagBase.h"
#include "NavalPort.h"

class BattleMap;

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

	bool IsCollideMapObstacle(cocos2d::Rect& rec);

	bool IsCollideNavalBase(ShipBase* pShip);

	bool IsCollideNavalFlag(ShipBase* pShip);

	void SetNavalBase(NavalBase* naval);
	NavalBase* GetNavalBase();

	void SetNavalFlagBase(BornEdgeType type, NavalFlagBase* pFlagBase);
	NavalFlagBase* GetNavalFlagBase(BornEdgeType type);

	void SetNavalPort(BornEdgeType type, NavalPort* pPort);
	NavalPort* GetNavalPort(BornEdgeType type);
protected:
	BattleMapManager();
	
	static BattleMapManager* m_Instance;

	BattleMap* m_CurBattleMap;

	BornEdgeType m_bTeamBornEdge;

	std::vector<MapCollision*> m_MapCollisions;

	NavalBase* m_NavalBase;

	std::map<BornEdgeType,NavalFlagBase*> m_NavalFlagBases;

	std::map<BornEdgeType, NavalPort*> m_NavalPorts;
};

#endif//__BATTLEMAP_MANAGER_H__
