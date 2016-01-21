#ifndef __GAME_ANIMATION_H__
#define __GAME_ANIMATION_H__

#include "cocos2d.h"
#include "GameAnimAction.h"

class GameAnimation : public cocos2d::Sprite
{
public:
	GameAnimation();
	~GameAnimation();

	virtual void onEnter() override;

	virtual void update(float dt);

	virtual void onExit() override;

	void AddAnim(std::string actionName, int framenum, int animTag, cocos2d::SEL_CallFunc ActionStartFunc, cocos2d::SEL_CallFunc ActionEndFunc);

	void PlayAnim(std::string actionName, float delaytime = 0.0f);

	void PlayAnimOnce(std::string actionName, float delaytime = 0.0f);

	void StopAnim();

	void InitSprite(std::string actionName);

	std::string GetCurActionName();

protected:
	//cocos2d::Vector<cocos2d::SpriteFrame*>
	std::map<std::string, GameAnimAction*> m_ActionDict;

	std::string m_CurAction;
};

#endif //__GAME_ANIMATION_H__

