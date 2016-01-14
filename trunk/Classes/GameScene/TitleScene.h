#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class TitleScene : cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onEnter() override;

	// implement the "static create()" method manually
	CREATE_FUNC(TitleScene);

protected:
	void loadRes();

};

#endif //__TITLE_SCENE_H__
