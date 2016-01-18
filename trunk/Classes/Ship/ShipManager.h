#ifndef __SHIP_MANAGER_H__
#define __SHIP_MANAGER_H__

#include <vector>
#include <map>
#include "ShipBase.h"

enum TeamShipSeat
{
	TeamShipSeat_1 = 0,
	TeamShipSeat_2,
	TeamShipSeat_3,
	TeamShipSeat_4,
	TeamShipSeat_5,
};

enum EnemyShipSeat
{
	EnemyShipSeat_1 = 0,
	EnemyShipSeat_2,
	EnemyShipSeat_3,
	EnemyShipSeat_4,
	EnemyShipSeat_5,
};

enum ShipType
{
	ShipType_Carrack = 0,
};

class ShipManager
{
public:	
	~ShipManager();

	static ShipManager* getInstance();

	//-------------------------------------
	void SetSelfShipSeat(TeamShipSeat seat);

	ShipBase* BornTeamShip(TeamShipSeat num, ShipType type = ShipType::ShipType_Carrack);

	ShipBase* BornEnemyShip(EnemyShipSeat num, ShipType type = ShipType::ShipType_Carrack);

	void ClearAll();

	ShipBase* GetTeamShip(TeamShipSeat num);

	ShipBase* GetEnemyShip(EnemyShipSeat num);

	ShipBase* GetSelfShip();
	//-------------------------------------

protected:
	ShipManager();

	static ShipManager* m_Instance;

protected:
	TeamShipSeat m_SelfShipSeat;

	std::map<TeamShipSeat, ShipBase*> m_TeamShips;

	std::map<EnemyShipSeat, ShipBase*> m_EnemyShips;
};

#endif//__SHIP_MANAGER_H__