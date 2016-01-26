#ifndef __PAY_SCENE_H__
#define __PAY_SCENE_H__

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



class MatchVSDemoPayScene :public CCLayer, public cocos2d::extension::EditBoxDelegate{
public:
    CREATE_FUNC(MatchVSDemoPayScene);
	~MatchVSDemoPayScene();

    static cocos2d::Scene* createScene();
    virtual bool init();

    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);



	void onClickClose(Ref* pSender, Widget::TouchEventType type);
	void onDemoScenceBack(Ref* pSender, Widget::TouchEventType type);
    void onDo_pay_matchvs(Ref* pSender, Widget::TouchEventType type);
    void onDo_pay_tianyi(Ref* pSender, Widget::TouchEventType type);
    void onDo_pay_baidu(Ref* pSender, Widget::TouchEventType type);
    void onDo_pay_ali(Ref* pSender, Widget::TouchEventType type);
    void onDo_pay_weixin(Ref* pSender, Widget::TouchEventType type);
    


    Label* jdisplay;
    void update(float dt);   //注意参数类型  
     MatchVSDemoLobbyPayBundle* m_fomain;
	std::string pay_str;

private:
    Button* buttonpay_matchvs;
    Button* buttonpay_ali;
    Button* buttonpay_tianyi;
    Button* buttonpay_baidu;
	Button* buttonpay_weixin;
	Button* buttonpay_close;
	Button* buttonpay_back;

	Vec2 origin;
	double vwtemp;
	double vhtemp;

	Button* getButton(const char * filepath1, const char * filepath2, double csw, double csh, double posw, double posh, const char *str);
};


#endif
