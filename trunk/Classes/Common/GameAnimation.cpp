#include "GameAnimation.h"


GameAnimation::GameAnimation()
{
}


GameAnimation::~GameAnimation()
{
}

void GameAnimation::update(float dt)
{
	cocos2d::Sprite::update(dt);
}

void GameAnimation::AddAnim(std::string actionName, int framenum, int animTag, cocos2d::SEL_CallFunc ActionStartFunc, cocos2d::SEL_CallFunc ActionEndFunc)
{
	if (m_ActionDict.find(actionName) == m_ActionDict.end())
	{
		GameAnimAction* pAction = new GameAnimAction(this, animTag);
		m_ActionDict[actionName] = pAction;

		pAction->SetActionStartFunc(ActionStartFunc);
		pAction->SetActionEndFunc(ActionEndFunc);

		pAction->InitResource(actionName,framenum);
	}
}

void GameAnimation::InitSprite(std::string actionName)
{
	std::string initName = actionName + "_0.png";
	initWithSpriteFrameName(initName);
	cocos2d::SpriteFrame* frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(initName);
}

void GameAnimation::PlayAnim(std::string actionName, float delaytime)
{
	if (actionName == m_CurAction)
	{
		return;
	}

	m_CurAction = actionName;

	std::map<std::string, GameAnimAction*>::iterator it = m_ActionDict.find(actionName);
	if (it != m_ActionDict.end())
	{
		GameAnimAction* pAction = it->second;
		if (pAction != nullptr)
		{
			pAction->PlayAction(delaytime);
		}
	}
}

void GameAnimation::PlayAnimOnce(std::string actionName, float delaytime)
{
	std::map<std::string, GameAnimAction*>::iterator it = m_ActionDict.find(actionName);
	if (it != m_ActionDict.end())
	{
		GameAnimAction* pAction = it->second;
		if (pAction != nullptr)
		{
			pAction->PlayActionOnce(delaytime);
		}
	}
}

void GameAnimation::StopAnim()
{
	m_CurAction = "";

	std::map<std::string, GameAnimAction*>::iterator it = m_ActionDict.find(m_CurAction);
	if (it != m_ActionDict.end())
	{
		GameAnimAction* pAction = it->second;
		if (pAction != nullptr)
		{
			pAction->StopAction();
		}
	}
}

std::string GameAnimation::GetCurActionName()
{
	return m_CurAction;
}

void GameAnimation::onEnter()
{
	cocos2d::Sprite::onEnter();
}

void GameAnimation::onExit()
{
	cocos2d::Sprite::onExit();
}

