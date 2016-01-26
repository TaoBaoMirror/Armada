#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
//引入头文件和命名空间
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include <sstream>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

#include "MatchVSDemoLobbyPay.h"
#include "MatchVSDemoUserBattle.h"
#include "MatchVSDemoScence.h"



class MatchVSDemoBattleScene: public CCLayer
{
public:
	CREATE_FUNC(MatchVSDemoBattleScene);

	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuCloseCallback(Ref* pSender, Widget::TouchEventType type);
	void menuHelloCallback(Ref* pSender, Widget::TouchEventType type);


	void touchEventbf(Ref* pSender, Widget::TouchEventType type);
	void touchEventad(Ref* pSender, Widget::TouchEventType type);
	void touchEventbgd(Ref* pSender, Widget::TouchEventType type);
	void touchEventbgf(Ref* pSender, Widget::TouchEventType type);
	void touchEventdr(Ref* pSender, Widget::TouchEventType type);
	void touchEventlui(Ref* pSender, Widget::TouchEventType type);
	void touchEventmr(Ref* pSender, Widget::TouchEventType type);
	void touchEventoll(Ref* pSender, Widget::TouchEventType type);

	cocos2d::ui::RichText* _richText;
	Label* jdisplay;




private:
	Button* buttonbf;
	Button* buttonad;
	Button* buttonbgd;
	Button* buttonbgf;
	Button* buttondr;
	Button* buttonlui;
	Button* buttonmr;
	Button* buttonoll;
	Button* buttonpay_close;
	Button* buttonpay_back;

	Vec2 origin;
	float vwtemp;
	float vhtemp;

	Button* getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str);
};







#endif