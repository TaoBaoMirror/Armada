#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//引入头文件和命名空间
#include "cocos-ext.h"
#include <sstream>
#include "MatchVSDemoCommon.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;


class MatchVSDemoScence : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback

	void menuCloseCallback(Ref* pSender, Widget::TouchEventType type);
    void touchEventpay(Ref *pSender, Widget::TouchEventType type);
	void touchEventlobby(Ref *pSender, Widget::TouchEventType type);
	void touchEventuser(Ref *pSender, Widget::TouchEventType type);
	void touchEventbattle(Ref *pSender, Widget::TouchEventType type);


	std::string myWrap(std::string str, int length);

    // implement the "static create()" method manually
    CREATE_FUNC(MatchVSDemoScence);

private:


	Button* buttonlobby;
	Button* buttonuser;
	Button* buttonbattle;
	Button* buttonpay;
	Button* buttonpay_close;

	Vec2 origin;
	float vwtemp;
	float vhtemp;

	void buttontrue(Button* bt);
	void buttonfalse(Button* bt);
	Button* getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str, bool invaild = true);



};

#endif // __HELLOWORLD_SCENE_H__
