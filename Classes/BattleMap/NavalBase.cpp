#include "NavalBase.h"


NavalBase::NavalBase()
{
}


NavalBase::~NavalBase()
{
}

bool NavalBase::CheckCollideShip(ShipBase* pShip)
{
	//�Ƿ��Ǽ����� ��Ѫ

	//�Ƿ������˶Է�������

	return false;
}

void NavalBase::InitNabalBase(cocos2d::Vec2 pos, cocos2d::Size size)
{
	m_BaseBoundingBox = cocos2d::Rect(pos, size);
}

void NavalBase::SetBelongToType(BornEdgeType type)
{
	m_bBelongToType = type;

	//set postion
}

BornEdgeType NavalBase::GetBelongType()
{
	return m_bBelongToType;
}
