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

	AddAnim("Ship_Carrack_Move", 1, 0, nullptr, nullptr);

	InitSprite("Ship_Carrack_Move");
}


Emplacement::~Emplacement()
{
	if (mGunEmitter) delete mGunEmitter;
}

void Emplacement::update(float dt)
{
	if (mGunEmitter != nullptr)
	{
		mGunEmitter->TickEmitter(dt);
	}
	//1 target���ڲ�����Ұ��
	if (m_LockTarget != nullptr && IsWithinRange())
	{
		//2 �Ƿ�cooldown�Ѿ������� 
		//  �����Ŀ��Ƕ���ĳ����ֵ�ڵĻ��ǵĻ� ����
		//  �����ٽ��ڿڵ�ת����׼����Ŀ����ת�Ƕ�
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
		//3 ���target������Ұ�� Ѱ����һ��target

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
	cocos2d::Vec2 shootdir = ori.rotateByAngle(pilot, m_CurDegree);
	mGunEmitter->SetShootDir(shootdir);
	mGunEmitter->Shot(BulletEmitter::custom_dir);
}

void Emplacement::RotToTargetShip(float dt)
{
	cocos2d::Vec2 targetPos = m_LockTarget->getPosition();

	cocos2d::Vec2 selfPos = this->getPosition();

	cocos2d::Vec2 curDir = targetPos - selfPos;
	curDir.normalize();

	float degree = curDir.getAngle();

	if (degree > m_CurDegree)
	{
		m_CurDegree += m_DegreeSpeed * dt;
	}
	else
	{
		m_CurDegree -= m_DegreeSpeed * dt;
	}

	this->setRotation(m_CurDegree);
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

	float degree = curDir.getAngle();

	float diffDegree = abs(degree - m_CurDegree);

	if (diffDegree < m_DegreeThreshold)
	{
		return true;
	}

	return false;
}
