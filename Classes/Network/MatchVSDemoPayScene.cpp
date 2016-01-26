#include "MatchVSDemoPayScene.h"



Scene* MatchVSDemoPayScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MatchVSDemoPayScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

MatchVSDemoPayScene::~MatchVSDemoPayScene()
{
}

// on "init" you need to initialize your instance
bool MatchVSDemoPayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	m_fomain = MatchVSDemoLobbyPayBundle::getInstance();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	vwtemp = visibleSize.width + origin.x;
	vhtemp = visibleSize.height + origin.y;



	/*
	CCMenuItemFont *closeItem = CCMenuItemFont::create("close", this, menu_selector(ScenePay::menuCloseCallback));//添加文字按钮，点击实现缩�?
	closeItem->setColor(ccc3(0, 255, 0));  //设置颜色
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width * 0.5,
	origin.y + closeItem->getContentSize().height / 2));

	CCMenuItemFont *backItem = CCMenuItemFont::create("Back", this, menu_selector(ScenePay::menuHelloCallback));//添加文字按钮，点击实现缩�?
	backItem->setColor(ccc3(0, 255, 0));  //设置颜色
	backItem->setPosition(Vec2(origin.x + visibleSize.width - backItem->getContentSize().width * 2,
	origin.y + backItem->getContentSize().height / 2));


	auto menu = Menu::create(closeItem, backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	*/

	LayerColor *logLay = LayerColor::create(Color4B(0x22, 0x11, 0x22, 255));
	logLay->setContentSize(Size(vwtemp * 24 / 40, vhtemp * 34 / 40));
	logLay->setPosition(Vec2(vwtemp * 15 / 40, vhtemp * 1 / 10));
	this->addChild(logLay);




	buttonpay_close = Button::create("9.png", "9.png");
	buttonpay_close->setScale9Enabled(true);
	buttonpay_close->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_close->setTitleFontSize(8);
	buttonpay_close->setPosition(Vec2(vwtemp - buttonpay_close->getContentSize().width / 2, origin.y + buttonpay_close->getContentSize().height / 2));
	buttonpay_close->setTitleText(("关闭"));
	buttonpay_close->setZoomScale(0.4f);
	buttonpay_close->setPressedActionEnabled(true);
	buttonpay_close->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoPayScene::onClickClose, this));
	this->addChild(buttonpay_close);

	buttonpay_back = Button::create("9.png", "9.png");
	buttonpay_back->setScale9Enabled(true);
	buttonpay_back->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_back->setTitleFontSize(8);
	buttonpay_back->setPosition(Vec2(vwtemp - buttonpay_back->getContentSize().width * 1.6, origin.y + buttonpay_back->getContentSize().height / 2));
	buttonpay_back->setTitleText(("返回"));
	buttonpay_back->setZoomScale(0.4f);
	buttonpay_back->setPressedActionEnabled(true);
	buttonpay_back->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoPayScene::onDemoScenceBack, this));
	this->addChild(buttonpay_back);


	buttonpay_matchvs = getButton("1.png", "1.png", vwtemp / 4, vhtemp * 6 / 40, vwtemp * 7 / 40, vhtemp * 35 / 40, ("matchvs"));
	buttonpay_matchvs->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoPayScene::onDo_pay_matchvs, this));
	this->addChild(buttonpay_matchvs);

	buttonpay_ali = getButton("2.png", "2.png", vwtemp / 4, vhtemp * 6 / 40, vwtemp * 7 / 40, vhtemp * 28 / 40, ("阿里"));
	buttonpay_ali->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoPayScene::onDo_pay_ali, this));
	this->addChild(buttonpay_ali);

	buttonpay_tianyi = getButton("3.png", "3.png", vwtemp / 4, vhtemp * 6 / 40, vwtemp * 7 / 40, vhtemp * 21 / 40, ("天翼"));
	buttonpay_tianyi->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoPayScene::onDo_pay_tianyi, this));
	this->addChild(buttonpay_tianyi);

	buttonpay_tianyi = getButton("4.png", "4.png", vwtemp / 4, vhtemp * 6 / 40, vwtemp * 7 / 40, vhtemp * 14 / 40, ("百度"));
	buttonpay_tianyi->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoPayScene::onDo_pay_baidu, this));
	this->addChild(buttonpay_tianyi);

	buttonpay_weixin = getButton("5.png", "5.png", vwtemp / 4, vhtemp * 6 / 40, vwtemp * 7 / 40, vhtemp * 7 / 40, ("微信"));
	buttonpay_weixin->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoPayScene::onDo_pay_weixin, this));
	this->addChild(buttonpay_weixin);



	std::string start_str = "display";
	jdisplay = Label::create(start_str, "fonts/arial.ttf", 12);//要显示的内容，字体，字号    
	jdisplay->setTag(100);
	jdisplay->setColor(ccc3(233, 255, 200));  //设置颜色  
	jdisplay->setDimensions(vwtemp * 23 / 40, vhtemp * 34 / 40);
	jdisplay->setPosition(Vec2(vwtemp * 27 / 40, vhtemp / 2));
	this->addChild(jdisplay, 2);


	m_fomain->set_str(&pay_str);
	this->scheduleUpdate();

	return true;
}

void MatchVSDemoPayScene::update(float dt)   //注意参数类型  
{
	DemoLock();
	//	const char * i = (pay_str.c_str());
	jdisplay->setString(pay_str);
	DemoUnlock();
}

void MatchVSDemoPayScene::onDo_pay_matchvs(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = m_fomain->Handle("pay_matchvs");
		break;
	}
	default:
		break;
	}
}

void MatchVSDemoPayScene::onDo_pay_ali(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = m_fomain->Handle("pay_ali");
	}
	break;
	default:
		break;
	}
}

void MatchVSDemoPayScene::onDo_pay_tianyi(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = m_fomain->Handle("pay_tianyi");
	}
	break;
	default:
		break;
	}
}

void MatchVSDemoPayScene::onDo_pay_baidu(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = m_fomain->Handle("pay_baidu");
	}
	break;
	default:
		break;
	}
}

void MatchVSDemoPayScene::onDo_pay_weixin(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = m_fomain->Handle("pay_weixin");
	}
	break;
	default:
		break;
	}
}


void MatchVSDemoPayScene::onClickClose(Ref* pSender, Widget::TouchEventType type)
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
void MatchVSDemoPayScene::onDemoScenceBack(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		CCDirector::sharedDirector()->replaceScene(MatchVSDemoScence::createScene());
		break;
	}
	
	default:
		break;
	}
}

void MatchVSDemoPayScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}
void MatchVSDemoPayScene::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}
void MatchVSDemoPayScene::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void MatchVSDemoPayScene::editBoxReturn(ui::EditBox* editBox)
{
	log("editBox %p was returned !", editBox);

	std::stringstream ss;
	int c;



}
Button* MatchVSDemoPayScene::getButton(const char * filepath1, const char * filepath2, double csw, double csh, double posw, double posh, const char *str)
{
	Button* buttontemp = Button::create(filepath1, filepath2);
	buttontemp->setScale9Enabled(true);
	buttontemp->setContentSize(Size(csw, csh));
	buttontemp->setTitleFontSize(8);
	buttontemp->setPosition(Vec2(posw, posh));

	buttontemp->setTitleText(str);
	buttontemp->setZoomScale(0.4f);
	buttontemp->setPressedActionEnabled(true);

	return buttontemp;

}


