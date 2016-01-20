#include "NavalFlagBase.h"


NavalFlagBase::NavalFlagBase()
{
}


NavalFlagBase::~NavalFlagBase()
{
}

void NavalFlagBase::SetBelongToType(BornEdgeType type)
{
	m_bBelongToType = type;
}

BornEdgeType NavalFlagBase::GetBelongType()
{
	return m_bBelongToType;
}

void NavalFlagBase::InitNabalFlagBase(cocos2d::Vec2 centerpos)
{
	//1 create flag
	m_Flag = new NavalFlag(m_bBelongToType);
	if (m_Flag != nullptr)
	{
		m_Flag->InitRes();
	}

	//2 set pos
	m_OriFlagPos = centerpos;

	if (m_Flag != nullptr)
	{
		m_Flag->setPosition(centerpos);
	}
}

bool NavalFlagBase::CheckCollideShip(ShipBase* pShip)
{
	if (m_Flag != nullptr)
	{
		if (m_Flag->IsEnableFlag())
		{
			if (pShip->GetBelongType() != m_Flag->GetBelongTo())
			{
				return true;
			}
		}
	}

	return false;
}

void NavalFlagBase::CatchFlag()
{
	m_Flag->SetDisableFlag();
}

void NavalFlagBase::RecoveryFlag()
{
	m_Flag->SetEnableFlag();

	m_OriFlagPos = m_OriFlagPos;
}

void NavalFlagBase::SetFlagAt(cocos2d::Vec2 pos)
{
	m_Flag->SetEnableFlag();

	m_OriFlagPos = pos;
}
