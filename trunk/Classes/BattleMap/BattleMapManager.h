#ifndef __BATTLEMAP_MANAGER_H__
#define __BATTLEMAP_MANAGER_H__

class BattleMap;

class BattleMapManager
{
public:	
	~BattleMapManager();

	static BattleMapManager* getInstance();

	BattleMap* GetBattleMap();

	bool LoadBattleMap(int num);

	void ReleaseBattleMap();

protected:
	BattleMapManager();
	
	static BattleMapManager* m_Instance;

	BattleMap* m_CurBattleMap;
};

#endif//__BATTLEMAP_MANAGER_H__
