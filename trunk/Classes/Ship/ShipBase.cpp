#include "ShipBase.h"
#include "Drive/Vehicle.h"
#include "Drive/World.h"
#include "Item/Buff.h"

ShipBase::ShipBase(): 
	Vehicle(World::GetInstance())
{
}


ShipBase::~ShipBase()
{
}

void ShipBase::SetResource(std::string name)
{
	//if (m_framesDict.size() == 0)
	//{
	//	int numAnim = m_ActionsFrameCount.size();
	//	//m_framesDict = new cocos2d::Map<std::string,cocos2d::Vector<cocos2d::SpriteFrame*>*>();
	//	m_framesDict.clear();
	//	for (int i = 0; i < numAnim; ++i)
	//	{
	//		cocos2d::Vector<cocos2d::SpriteFrame*> temp; //= new cocos2d::Vector<cocos2d::SpriteFrame*>();

	//		int numAction = m_ActionsFrameCount.at(i).asInt();
	//		for (int k = 0; k < numAction; ++k)
	//		{
	//			std::string frameName = ActionsName[i];

	//			std::stringstream ss;
	//			ss << k;
	//			std::string kStr = ss.str();
	//			frameName = name + "_" + frameName + "_" + kStr + ".png";

	//			cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);

	//			if (spriteframe != nullptr)
	//			{
	//				temp.pushBack(spriteframe);
	//			}
	//			//
	//			if (k == numAction - 1)
	//			{
	//				if (temp.size() != 0)
	//				{
	//					m_framesDict.insert(std::pair<std::string, cocos2d::Vector<cocos2d::SpriteFrame*>>(ActionsName[i], temp));
	//				}
	//				break;
	//			}
	//		}
	//	}
	//}

	//std::string initName = name + "_" + ActionsName[0] + "_0.png";
	//initWithSpriteFrameName(initName);
	//cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(initName);
}

void ShipBase::ShipBattleCtrl(ShipCtrlType type, ShipCtrlEvent evt)
{

}


void ShipBase::UpdateShip(float dt)
{
	GameAnimation::update(dt);
	UpdateBuffList(dt);
}

void ShipBase::InitShip()
{

}
//----------------------------------
void ShipBase::SetBelongType(BornEdgeType type)
{
	m_bBelongType = type;
}

BornEdgeType ShipBase::GetBelongType()
{
	return m_bBelongType;
}

void ShipBase::AddBuff(Buff* buff)
{
	mBuffList.push_back(buff);
	//
	buff->SetBearer(this);
	buff->BuffOn();
	buff->OnAttachShip();
}

void ShipBase::RemoveBuff(Buff* buff, bool clearup)
{
	buff->OnDetachShip();
	//
	if (clearup)
	{
		mBuffList.remove(buff);
	}
	//
	delete buff;
}

void ShipBase::UpdateBuffList(float dt)
{
	std::list<Buff*>::iterator it = mBuffList.begin();
	while (it != mBuffList.end())
	{
		Buff* buff = *it;
		buff->UpdateBuff(dt);
		//
		if (buff->IsEnable() == false)
		{
			it = mBuffList.erase(it);
			//
			RemoveBuff(buff, false);
		}
		else
		{
			it++;
		}
	}
}
