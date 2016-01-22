#ifndef __GAME_ANIM_ACTION_H__
#define __GAME_ANIM_ACTION_H__

#include "cocos2d.h"

class GameAnimation;

class GameAnimAction
{
public:
	GameAnimAction(GameAnimation* anim, int ActionTag);
	~GameAnimAction();

	void InitResource(std::string name, int framenum);

	void PlayAction(float delay = 0.0f);

	void PlayActionOnce(float delay = 0.0f);

	void StopAction();

	void SetActionStartFunc(cocos2d::SEL_CallFunc func, cocos2d::Ref* target);
	void SetActionEndFunc(cocos2d::SEL_CallFunc func, cocos2d::Ref* target);
	void SetActionUpdateFunc(cocos2d::SEL_CallFunc func);

protected:
	void onOnceAnimOver();

	std::string m_ActionName;
	int m_ActionFrameNum;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_Frames;

	GameAnimation* m_Animation;

	int m_ActionTag;

	cocos2d::Ref* m_StartFuncTarget;
	cocos2d::Ref* m_StopFuncTarget;
	cocos2d::SEL_CallFunc ActionStartFunc;
	cocos2d::SEL_CallFunc ActionEndFunc;
	cocos2d::SEL_CallFunc ActionUpdateFunc;
};

#endif //__GAME_ANIM_ACTION_H__