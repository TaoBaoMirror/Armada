#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
//引入头文件和命名空间
#include "cocos-ext.h"
#include <sstream>

USING_NS_CC;
USING_NS_CC_EXT;
//using namespace cocos2d::ui;
#include "CommonMutex.h"
#include "MatchVSDemoLobbyPay.h"
#include "MatchVSDemoUserBattle.h"
#include "MatchVSDemoScence.h"
#include "ui/CocosGUI.h"
#include "stdlib.h"





#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))

#else // defined(__linux__) || defined(__linux)

#include<iostream>
#include<string>
#include <wctype.h>
#include <wchar.h>


#endif

class MatchVSDemoLobbyScene:public CCLayer , public cocos2d::extension::EditBoxDelegate
{
public:
	CREATE_FUNC(MatchVSDemoLobbyScene);
	~MatchVSDemoLobbyScene();

	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuCloseCallback(Ref* pSender, Widget::TouchEventType type);
	void menuHelloCallback(Ref* pSender, Widget::TouchEventType type);

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	
	void u_gameloginCallback(Ref* pSender, Widget::TouchEventType type);
	
	void u_roominCallback(Ref* pSender, Widget::TouchEventType type);
	void u_readyCallback(Ref* pSender, Widget::TouchEventType type);
	void u_startCallback(Ref* pSender, Widget::TouchEventType type);
	void u_send_randCallback(Ref* pSender, Widget::TouchEventType type);
	void u_gamelogoutCallback(Ref* pSender, Widget::TouchEventType type);
	void u_roomoutCallback(Ref* pSender, Widget::TouchEventType type);
	void u_gameoverCallback(Ref* pSender, Widget::TouchEventType type);
	void u_send_sreliableCallback(Ref* pSender, Widget::TouchEventType type);
	void u_clearCallback(Ref* pSender, Widget::TouchEventType type);

	void buttontrue(Button* bt);
	void buttonfalse(Button* bt);
	void update(float dt);   //注意参数类型  


	cocos2d::ui::EditBox* _editName;
	Label* jdisplay;
	MatchVSDemoLobbyPayBundle* m_fomain;


private:
	Button* buttonglogin;
	Button* buttonrin;
	Button* buttonready;
	Button* buttonstart;
	Button* buttonsrand;
	Button* buttongout;
	Button* buttonrout;
	Button* buttongover;
	Button* buttonsendreliable;
	Button* buttonpay_close;
	Button* buttonpay_back;
	Button* buttonclear;

	cocos2d::ui::RichText *Textowner;


	std::string lobby_str;
	Vec2 origin;
	float vwtemp;
	float vhtemp;
	Button* getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str, bool invaild = true);
	bool displayOwnerID();

};


#endif