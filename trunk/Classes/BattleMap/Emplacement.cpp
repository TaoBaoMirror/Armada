#include "Emplacement.h"
#include "Ship\ShipManager.h"


Emplacement::Emplacement(BornEdgeType edgetype) :
m_EdgeType(edgetype),
m_Range(200.0f),
m_CurDegree(0.0f),
m_DegreeThreshold(5.0f),
m_DegreeSpeed(60.0f),
m_LockTarget(nullptr)
{
	mGunEmitter = new BulletEmitter(nullptr);

	mGunEmitter->SetMaxColdDown(3.0f);

	AddAnim("Ship_Carrack_Move", 1, 0, nullptr, nullptr);

	InitSprite("Ship_Carrack_Move");
}


Emplacement::~Emplacement()
{
	if (mGunEmitter) delete mGunEmitter;
}

void Emplacement::InitRot(float rot)
{
	m_CurDegree = rot;

	this->setRotation(-m_CurDegree);
}

void Emplacement::update(float dt)
{
	if (mGunEmitter != nullptr)
	{
		mGunEmitter->TickEmitter(dt);
	}
	//1 target还在不在视野内
	if (m_LockTarget != nullptr && IsWithinRange())
	{
		//2 是否cooldown已经结束了 
		//  如果与目标角度在某个阈值内的话是的话 开火
		//  否则再将炮口调转到瞄准现在目标旋转角度
		if (IsAttackCoolDownOver() && IsWithinDegree())
		{
			AttackTargetShip();
		}
		else
		{
			RotToTargetShip(dt);
		}
	}
	else
	{
		//3 如果target不在视野了 寻找下一个target

		FindTargetShip();
	}
}

void Emplacement::FindTargetShip()
{
	ShipBase* findship = nullptr;

	if (m_EdgeType == BornEdgeType::BornEdgeType_Left)
	{
		findship = ShipManager::getInstance()->FindShipByDistance(BornEdgeType::BornEdgeType_Right, this->getPosition(), m_Range);
	}
	else if (m_EdgeType == BornEdgeType::BornEdgeType_Right)
	{
		findship = ShipManager::getInstance()->FindShipByDistance(BornEdgeType::BornEdgeType_Left, this->getPosition(), m_Range);
	}	

	m_LockTarget = findship;
}

void Emplacement::AttackTargetShip()
{
	mGunEmitter->SetEmitterPos(this->getPosition());
	cocos2d::Vec2 ori = cocos2d::Vec2(1.0f, 0.0f);
	cocos2d::Vec2 pilot = cocos2d::Vec2(0.0f,0.0f);
	float angle = CC_DEGREES_TO_RADIANS(m_CurDegree);
	cocos2d::Vec2 shootdir = ori.rotateByAngle(pilot, angle);
	mGunEmitter->SetShootDir(shootdir);
	mGunEmitter->Shot(BulletEmitter::custom_dir);
}

void Emplacement::RotToTargetShip(float dt)
{
	cocos2d::Vec2 targetPos = m_LockTarget->getPosition();

	cocos2d::Vec2 selfPos = this->getPosition();

	cocos2d::Vec2 curDir = targetPos - selfPos;
	curDir.normalize();

	float angle = curDir.getAngle();
	float degree = CC_RADIANS_TO_DEGREES(angle);

	if (m_CurDegree > degree)
	{
		if ((m_CurDegree - 180.0f) > degree)
		{
			m_CurDegree += m_DegreeSpeed * dt;
		}
		else
		{
			m_CurDegree -= m_DegreeSpeed * dt;
		}
		
	}
	else
	{
		if ((m_CurDegree + 180.0f) < degree)
		{
			m_CurDegree -= m_DegreeSpeed * dt;
		}
		else
		{
			m_CurDegree += m_DegreeSpeed * dt;
		}
	}

	if (m_CurDegree > 180.0f)
	{
		m_CurDegree -= 360.0f;
	}

	if (m_CurDegree < -180.0f)
	{
		m_CurDegree += 360.0f;
	}

	this->setRotation(-m_CurDegree);
}

bool Emplacement::IsAttackCoolDownOver()
{
	if (mGunEmitter->ColdDownTimer() > 0.0f)
	{
		return false;
	}

	return true;
}

bool Emplacement::IsWithinRange()
{
	cocos2d::Vec2 targetPos = m_LockTarget->getPosition();

	cocos2d::Vec2 selfPos = this->getPosition();

	float dis = selfPos.distance(targetPos);

	if (dis < m_Range)
	{
		return true;
	}

	m_LockTarget = nullptr;

	return false;
}

bool Emplacement::IsWithinDegree()
{
	cocos2d::Vec2 targetPos = m_LockTarget->getPosition();

	cocos2d::Vec2 selfPos = this->getPosition();

	cocos2d::Vec2 curDir = targetPos - selfPos;
	curDir.normalize();

	float angle = curDir.getAngle();
	float degree = CC_RADIANS_TO_DEGREES(angle);

	float diffDegree = abs(degree - m_CurDegree);

	if (diffDegree > 180.0f)
	{
		diffDegree = 360.0f - diffDegree;
	}

	if (diffDegree < m_DegreeThreshold)
	{
		return true;
	}

	return false;
}
