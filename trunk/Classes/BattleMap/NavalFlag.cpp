#include "NavalFlag.h"


NavalFlag::NavalFlag(BornEdgeType type)
{
}


NavalFlag::~NavalFlag()
{
}

void NavalFlag::InitRes()
{

}

void NavalFlag::SetEnableFlag()
{
	m_bIsEnable = true;

	this->setVisible(true);
}

bool NavalFlag::IsEnableFlag()
{
	return m_bIsEnable;
}


void NavalFlag::SetDisableFlag()
{
	m_bIsEnable = false;

	this->setVisible(false);
}

bool NavalFlag::IsCatchFlag(ShipBase* pShip)
{
	//??


	//
	return false;
}

BornEdgeType NavalFlag::GetBelongTo()
{
	return m_bBelongToType;
}
