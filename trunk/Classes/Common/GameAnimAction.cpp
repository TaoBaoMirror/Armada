#include "GameAnimAction.h"
#include "GameAnimation.h"


GameAnimAction::GameAnimAction(GameAnimation* anim, int ActionTag) :
m_Animation(anim),
m_ActionTag(ActionTag)
{
}


GameAnimAction::~GameAnimAction()
{
}

void GameAnimAction::InitResource(std::string name, int framenum)
{
	m_ActionFrameNum = framenum;
	m_ActionName = name;

	for (int k = 0; k < m_ActionFrameNum; ++k)
	{
		std::string frameName = "";

		std::stringstream ss;
		ss << k;
		std::string kStr = ss.str();
		frameName = m_ActionName + "_" + kStr + ".png";

		cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);

		if (spriteframe != nullptr)
		{
			m_Frames.pushBack(spriteframe);
		}
	}
}


void GameAnimAction::PlayAction(float delay)
{
	if (m_Animation == nullptr)
	{
		return;
	}
	m_Animation->stopAllActions();

	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(m_Frames, 0.1f);
	CC_ASSERT(ani);
	cocos2d::Animate* animate = cocos2d::Animate::create(ani);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animate);
	pRepeat->setTag(m_ActionTag);
	m_Animation->runAction(pRepeat);

	if (ActionStartFunc != nullptr)
	{
		ActionStartFunc;
	}
}

void GameAnimAction::PlayActionOnce(float delay)
{
	if (m_Animation == nullptr)
	{
		return;
	}

	cocos2d::Vector<cocos2d::FiniteTimeAction*> pAcs;

	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(m_Frames, 0.1f);
	CC_ASSERT(ani);
	cocos2d::Animate* animate = cocos2d::Animate::create(ani);
	pAcs.pushBack(animate);

	
	auto cbfunc = cocos2d::CallFunc::create(CC_CALLBACK_0(GameAnimAction::onOnceAnimOver, this));

	pAcs.pushBack(cbfunc);
	

	auto seq = cocos2d::Sequence::create(pAcs);
	seq->setTag(m_ActionTag);

	m_Animation->runAction(seq);

	if (ActionStartFunc != nullptr)
	{
		ActionStartFunc;
	}
}

void GameAnimAction::StopAction()
{
	if (m_Animation == nullptr)
	{
		return;
	}

	m_Animation->stopActionByTag(m_ActionTag);

	if (ActionEndFunc != nullptr)
	{
		ActionEndFunc;
	}
}

void GameAnimAction::SetActionStartFunc(cocos2d::SEL_CallFunc func)
{
	ActionStartFunc = func;
}

void GameAnimAction::SetActionEndFunc(cocos2d::SEL_CallFunc func)
{
	ActionEndFunc = func;
}

void GameAnimAction::SetActionUpdateFunc(cocos2d::SEL_CallFunc func)
{
	ActionUpdateFunc = func;
}

void GameAnimAction::onOnceAnimOver()
{
	if (ActionEndFunc != nullptr)
	{
		ActionEndFunc;
	}
}
