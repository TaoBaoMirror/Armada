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
//
//enum EnemyShipSeat
//{
//	EnemyShipSeat_1 = 0,
//	EnemyShipSeat_2,
//	EnemyShipSeat_3,
//	EnemyShipSeat_4,
//	EnemyShipSeat_5,
//};

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
	void Update(float dt);
	//-------------------------------------
	void SetSelfShipSeat(BornEdgeType borntype,TeamShipSeat seat);

	//ShipBase* BornTeamShip(TeamShipSeat num, ShipType type = ShipType::ShipType_Carrack);

	//ShipBase* BornEnemyShip(TeamShipSeat num, ShipType type = ShipType::ShipType_Carrack);

	ShipBase* BornShip(BornEdgeType borntype, TeamShipSeat num, ShipType type = ShipType::ShipType_Carrack);

	void ClearAll();

	//ShipBase* GetTeamShip(TeamShipSeat num);

	//ShipBase* GetEnemyShip(TeamShipSeat num);

	ShipBase* GetShip(BornEdgeType borntype, TeamShipSeat num);

	ShipBase* GetSelfShip();
	//-------------------------------------

protected:
	ShipManager();

	static ShipManager* m_Instance;

protected:
	BornEdgeType m_SelfBornEdgeType;
	TeamShipSeat m_SelfShipSeat;

	std::map<TeamShipSeat, ShipBase*> m_Team_Left_Ships;

	std::map<TeamShipSeat, ShipBase*> m_Team_Right_Ships;
};

#endif//__SHIP_MANAGER_H__