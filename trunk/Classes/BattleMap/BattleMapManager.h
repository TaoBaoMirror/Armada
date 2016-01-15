#ifndef __BATTLEMAP_MANAGER_H__
#define __BATTLEMAP_MANAGER_H__

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

protected:
	BattleMapManager();
	
	static BattleMapManager* m_Instance;

	BattleMap* m_CurBattleMap;

	BornEdgeType m_bTeamBornEdge;
};

#endif//__BATTLEMAP_MANAGER_H__
