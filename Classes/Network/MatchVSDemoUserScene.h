#ifndef __USER_SCENE_H__
#define __USER_SCENE_H__

#include "cocos2d.h"

#include "cocos-ext.h"
#include <sstream>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

#include "MatchVSDemoLobbyPay.h"
#include "MatchVSDemoUserBattle.h"
#include "MatchVSDemoScence.h"
#include "ui/CocosGUI.h"
#include "MatchVSBase.h"
#include "MatchVSDemoCommon.h"

class MatchVSDemoUserScene : public CCLayer, public CMatchVSUserCallback
{
public:
	CREATE_FUNC(MatchVSDemoUserScene);

	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuCloseCallback(Ref* pSender, Widget::TouchEventType type);
	void menuHelloCallback(Ref* pSender, Widget::TouchEventType type);

	void u_registerCallback(Ref* pSender, Widget::TouchEventType type);
	void u_logingCallback(Ref* pSender, Widget::TouchEventType type);
	void u_getuserinfoCallback(Ref* pSender, Widget::TouchEventType type);
	void u_changeuserinfoCallback(Ref* pSender, Widget::TouchEventType type);


	cocos2d::ui::RichText* _richText;
    cocos2d::ui::RichText* _richUserID;
    cocos2d::ui::RichText* _richNickName;
    

	Label* jdisplay;

    ms_int32_t  onError(ms_int32_t i32Errno);
    ms_int32_t onGetUserInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
    ms_int32_t  onRegitBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
    ms_int32_t  onLoginBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
    ms_int32_t onChangeUserInfoBack(ms_int32_t i32Error, ms_int32_t i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
    ms_int32_t onLoginBackWithInfo(CMatchVSUserInfo *pUserInfo, int errCode);

    void whenImageDownLoad(CCNode* srcNode, CCSpriteFrame* downFrame);

    CCNode *_avatarNode;
private:
	Button* buttonbgf;
	Button* buttonbf;
	Button* buttonad;
	Button* buttonbgd;	
	Button* buttonpay_close;
	Button* buttonpay_back;

    std::string  m_strNickName;
    std::string  m_strUserID;
    std::string  m_strToken;
    std::string  m_strAvatar;

	void buttontrue(Button* bt);
	void buttonfalse(Button* bt);

	Vec2 origin;
	float vwtemp;
	float vhtemp;

	Button* getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str, bool invaild = true);

};




#endif