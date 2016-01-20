#ifndef __READY_BORN_H__
#define __READY_BORN_H__

#include "cocos2d.h"
#include "Ship\ShipManager.h"

class ReadyBorn
{
public:
	ReadyBorn(BornEdgeType edgeType, TeamShipSeat readyBornSeat);
	~ReadyBorn();

	void Update(float dt);

	void EnableReadyBorn();
	bool IsReadyBorn();

	bool CanBorn();

	void Born(cocos2d::Vec2 pos);
private:
	BornEdgeType m_EdgeType;
	TeamShipSeat m_ReadyBornSeat;

	float MaxWaitTime;
	float m_CurWaitTime;

	bool m_bCanBorn;
	bool m_bIsReadyBorn;
};

#endif //__READY_BORN_H__