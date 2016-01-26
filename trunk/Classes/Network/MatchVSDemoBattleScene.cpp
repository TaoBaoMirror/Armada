#include "MatchVSDemoBattleScene.h"


Scene* MatchVSDemoBattleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MatchVSDemoBattleScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MatchVSDemoBattleScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	vwtemp = visibleSize.width + origin.x;
	vhtemp = visibleSize.height + origin.y;


	LayerColor *logLay = LayerColor::create(Color4B(0x22, 0x11, 0x22, 255));
	logLay->setContentSize(Size(vwtemp * 7.6 / 15, vhtemp * 32 / 35));
	logLay->setPosition(Vec2(vwtemp * 7.2 / 15, vhtemp * 2.5 / 35));
	this->addChild(logLay);


	//----------------按钮------------------



	buttonpay_close = Button::create("9.png", "9.png");
	buttonpay_close->setScale9Enabled(true);
	buttonpay_close->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_close->setTitleFontSize(8);
	buttonpay_close->setPosition(Vec2(vwtemp - buttonpay_close->getContentSize().width / 2, origin.y + buttonpay_close->getContentSize().height / 2));
	buttonpay_close->setTitleText(("关闭"));
	buttonpay_close->setZoomScale(0.4f);
	buttonpay_close->setPressedActionEnabled(true);
	buttonpay_close->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::menuCloseCallback, this));
	this->addChild(buttonpay_close);

	buttonpay_back = Button::create("9.png", "9.png");
	buttonpay_back->setScale9Enabled(true);
	buttonpay_back->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_back->setTitleFontSize(8);
	buttonpay_back->setPosition(Vec2(vwtemp - buttonpay_back->getContentSize().width * 1.6, origin.y + buttonpay_back->getContentSize().height / 2));
	buttonpay_back->setTitleText(("返回"));
	buttonpay_back->setZoomScale(0.4f);
	buttonpay_back->setPressedActionEnabled(true);
	buttonpay_back->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::menuHelloCallback, this));
	this->addChild(buttonpay_back);

	buttonbf = getButton("1.png", "1.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 32 / 35, ("(getBattleFields)"));
	buttonbf->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventbf, this));
	this->addChild(buttonbf);

	buttonad = getButton("2.png", "2.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 27 / 35, ("(getAllDetail)"));
	buttonad->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventad, this));
	this->addChild(buttonad);

	buttonbgd = getButton("3.png", "3.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 22 / 35, ("(getBattleGameDetail)"));
	buttonbgd->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventbgd, this));
	this->addChild(buttonbgd);

	buttonbgf = getButton("4.png", "4.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 17 / 35, ("(getBattleGameFields)"));
	buttonbgf->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventbgf, this));
	this->addChild(buttonbgf);

	buttondr = getButton("5.png", "5.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 22 / 35, ("(GetDayRank)"));
	buttondr->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventdr, this));
	this->addChild(buttondr);

	buttonlui = getButton("6.png", "6.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 32 / 35, ("(getLobbyUserInfo)"));
	buttonlui->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventlui, this));
	this->addChild(buttonlui);

	buttonmr = getButton("7.png", "7.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 27 / 35, ("(GetMyRank)"));
	buttonmr->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventmr, this));
	this->addChild(buttonmr);

	buttonoll = getButton("8.png", "8.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 17 / 35, ("(GetOnlineList)"));
	buttonoll->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoBattleScene::touchEventoll, this));
	this->addChild(buttonoll);



	//--------------显示结果--------------------



	std::string start_str = "display";
	jdisplay = Label::create(start_str, "fonts/arial.ttf", 12);//要显示的内容，字体，字号
	jdisplay->setTag(100);
	jdisplay->setColor(ccc3(0, 255, 0));  //设置颜色  
	jdisplay->setDimensions(vwtemp / 4 * 3, vhtemp * 0.8);
	jdisplay->setPosition(Vec2(vwtemp * 0.65, vhtemp * 0.5));
	//this->addChild(jdisplay, 2);



	_richText = RichText::create();
	_richText->ignoreContentAdaptWithSize(false);
	_richText->ignoreContentAdaptWithSize(false);
	_richText->setContentSize(Size(vwtemp * 7.6 / 15, vhtemp * 33 / 35));
	_richText->setPosition(Vec2(vwtemp * 11 / 15, vhtemp * 15 / 35));
	_richText->setLocalZOrder(10);

	this->addChild(_richText);
	RichElementText* re6 = RichElementText::create(7, Color3B::ORANGE, 255, "display", "fonts/arial.ttf", 10);
	_richText->pushBackElement(re6);
	
	return true;
}




void MatchVSDemoBattleScene::menuCloseCallback(Ref* pSender, Widget::TouchEventType type)
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
void MatchVSDemoBattleScene::menuHelloCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		CCDirector::sharedDirector()->replaceScene(MatchVSDemoScence::createScene());
	}
	break;
	default:
		break;
	}
}


void MatchVSDemoBattleScene::touchEventbf(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = fortestuserbattlemain('b', "GetBattleFields");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoBattleScene::touchEventad(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = fortestuserbattlemain('b', "getAllDetail");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoBattleScene::touchEventbgd(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = fortestuserbattlemain('b', "getBattleGameDetail");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoBattleScene::touchEventbgf(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = fortestuserbattlemain('b', "getBattleGameFields");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoBattleScene::touchEventdr(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = fortestuserbattlemain('b', "GetDayRank");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoBattleScene::touchEventlui(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{

		const char * i = fortestuserbattlemain('b', "getLobbyUserInfo");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoBattleScene::touchEventmr(Ref* pSender, Widget::TouchEventType type)
{ 
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = fortestuserbattlemain('b', "GetMyRank");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoBattleScene::touchEventoll(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = fortestuserbattlemain('b', "GetOnlineList");
		
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
		//	jdisplay->setString(i);
	}
	break;
	default:
		break;
	}
}


Button* MatchVSDemoBattleScene::getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str)
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


