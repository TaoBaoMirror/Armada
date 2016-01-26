#include "MatchVSDemoScence.h"
#include "MatchVSDemoLobbyPay.h"
#include "MatchVSDemoUserBattle.h"


#include "MatchVSDemoUserScene.h"
#include "MatchVSDemoBattleScene.h"
#include "MatchVSDemoLobbyScene.h"
#include "MatchVSDemoPayScene.h"


#pragma comment(lib,"MatchSDK.lib")  


USING_NS_CC;

Scene* MatchVSDemoScence::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MatchVSDemoScence::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MatchVSDemoScence::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	vwtemp = visibleSize.width + origin.x;
	vhtemp = visibleSize.height + origin.y;

//----------------按钮------------------



    buttonpay_close = Button::create("9.png", "9.png");
	buttonpay_close->setScale9Enabled(true);
	buttonpay_close->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_close->setTitleFontSize(8);
	buttonpay_close->setPosition(Vec2(vwtemp - buttonpay_close->getContentSize().width / 2, origin.y + buttonpay_close->getContentSize().height / 2));
	buttonpay_close->setTitleText(("关闭"));
	buttonpay_close->setZoomScale(0.4f);
	buttonpay_close->setPressedActionEnabled(true);
	buttonpay_close->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoScence::menuCloseCallback, this));
	this->addChild(buttonpay_close);



	bool haveuseid = false;
	haveuseid = HaveSetUserToken();


	buttonuser = getButton("2.png", "2.png", vwtemp / 5, vhtemp * 2 / 3, vwtemp * 5 / 40, vhtemp / 2, ("用户"),true);
	buttonuser->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoScence::touchEventuser, this));
	this->addChild(buttonuser);

	buttonlobby = getButton("1.png", "1.png", vwtemp / 5, vhtemp * 2 / 3, vwtemp * 15 / 40, vhtemp / 2, ("大厅"), haveuseid);
	buttonlobby->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoScence::touchEventlobby, this));
	this->addChild(buttonlobby);


	buttonbattle = getButton("2.png", "2.png", vwtemp / 5, vhtemp * 2 / 3, vwtemp * 25 / 40, vhtemp / 2, ("战况"), haveuseid);
	buttonbattle->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoScence::touchEventbattle, this));
	this->addChild(buttonbattle);

	buttonpay = getButton("1.png", "1.png", vwtemp / 5, vhtemp * 2 / 3, vwtemp * 35 / 40, vhtemp / 2, ("支付"), haveuseid);
	buttonpay->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoScence::touchEventpay, this));
	this->addChild(buttonpay);

//-------------------------------------------------





    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("Hello World", "Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
  //  this->addChild(label, 1);

    // add "HelloWorld" splash screen"
 //   auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
 //   sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
  //  this->addChild(sprite, 0);
    

    return true;
}


void MatchVSDemoScence::menuCloseCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
	break;
	default:
		break;
	}
	}


void MatchVSDemoScence::touchEventpay(Ref *pSender, Widget::TouchEventType type)
{
    switch (type)
    {
    case Widget::TouchEventType::ENDED:
    {
        CCDirector::sharedDirector()->replaceScene(MatchVSDemoPayScene::createScene());
    }
    break;
    default:
        break;
    }
}


void MatchVSDemoScence::touchEventlobby(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		{
			CCDirector::sharedDirector()->replaceScene(MatchVSDemoLobbyScene::createScene());
		}
	break;
	default:
		break;
	}
}
void MatchVSDemoScence::touchEventuser(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		CCDirector::sharedDirector()->replaceScene(MatchVSDemoUserScene::createScene());
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoScence::touchEventbattle(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		CCDirector::sharedDirector()->replaceScene(MatchVSDemoBattleScene::createScene());
	}
	break;
	default:
		break;
	}
}

void MatchVSDemoScence::buttontrue(Button* bt)
{

	bt->setBright(true);
	bt->setEnabled(true);
}
void MatchVSDemoScence::buttonfalse(Button* bt)
{
	bt->setBright(false);
	bt->setEnabled(false);

}

Button* MatchVSDemoScence::getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str, bool invaild)
{
	Button* buttontemp = Button::create(filepath1, filepath2);
	buttontemp->setScale9Enabled(true);
	buttontemp->setContentSize(Size(csw, csh));
	buttontemp->setTitleFontSize(8);
	buttontemp->setPosition(Vec2(posw, posh));

	buttontemp->setTitleText(str);
	buttontemp->setZoomScale(0.4f);
	buttontemp->setPressedActionEnabled(true);

	if (invaild == false)
		buttonfalse(buttontemp);


	return buttontemp;

}





std::string MatchVSDemoScence::myWrap(std::string str, int length)
{
	unsigned int beginPos = 0;  //字符串的初始位置
	std::string resultStr;		//返回的字符串


	std::vector<std::string > str_vec;  //创建一个字符串类型的顺序容器
	do
	{
		str_vec.push_back(str.substr(beginPos, length)); //substr函数的作用类似剪刀，将str中从beginPos到length之间的字符串剪下来，单独放入容器中 
		if (beginPos + length >str.size())
		{
			break;  //当要裁剪的长度超出str的长度，则退出循环
		}
		else
		{
			beginPos += length;
		}

	} while (true);

	for (unsigned int i = 0; i<str_vec.size(); ++i)
	{
		resultStr.append(str_vec.at(i)).append("\n");
	}


	return resultStr;
}







