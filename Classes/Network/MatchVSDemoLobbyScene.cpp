#include "MatchVSDemoLobbyScene.h"
#include "MatchVSDemoCommon.h"
#include "BattleMap\BattleMapManager.h"
#include "GameManager\GameManager.h"

//int for_sendrand= 0;
//int for_gameover = 0;



Scene* MatchVSDemoLobbyScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MatchVSDemoLobbyScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
MatchVSDemoLobbyScene::~MatchVSDemoLobbyScene()
{
	ClearALL();

}


// on "init" you need to initialize your instance
bool MatchVSDemoLobbyScene::init()
{

	//const char *p = WStrToUTF8(L"�?d54�?)").c_str();
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





	//----------------编辑�?-----------------------

	std::string pNormalSprite = "8.png";
	_editName = ui::EditBox::create(Size(vwtemp* 0.2, vhtemp * 0.1), ui::Scale9Sprite::create(pNormalSprite));
	_editName->setPosition(Vec2(vwtemp * 31 / 35, vhtemp * 32 / 35));
	_editName->setFontName("Paint Boy");
	_editName->setFontSize(10);
	_editName->setFontColor(Color3B::RED);
	_editName->setPlaceHolder("input:");
	_editName->setPlaceholderFontColor(Color3B::WHITE);
	_editName->setMaxLength(30);
	_editName->setBright(false);
	_editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	_editName->setDelegate(this);
	//this->addChild(_editName, 3);

	int userid;
	char  struserid[25];
	userid = GetUserID();
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	sprintf_s(struserid, sizeof(struserid), "|My ID:%d", userid);
#else // defined(__linux__) || defined(__linux)
	sprintf(struserid, "|My ID:%d", userid);
#endif
	//LOGI("#***11 Label::createWithTTF userID: %s", struserid);
	std::string strUserId(struserid);
	Label *label = Label::createWithTTF(strUserId, "fonts/arial.ttf", 15);
	//LOGI("#***22 Label::createWithTTF userID: %s", struserid);
	label->setPosition(Vec2(vwtemp * 31 / 35, vhtemp * 32 / 35));
	//LOGI("#***33 Label::createWithTTF userID: %s", struserid);
	this->addChild(label, 1);
	//label->release();
	//LOGI("#***44 Label::createWithTTF userID: %s", struserid);



	RichElementText* rt2 = RichElementText::create(7, Color3B::WHITE, 255, "", "fonts/arial.ttf", 15);
	Textowner = RichText::create();
	Textowner->ignoreContentAdaptWithSize(false);
	Textowner->setContentSize(Size(vwtemp * 5 / 15, vhtemp * 4 / 35));
	Textowner->setPosition(Vec2(vwtemp * 10 / 15, vhtemp * 31 / 35));
	Textowner->pushBackElement(rt2);
	Textowner->setLocalZOrder(10);
	this->addChild(Textowner);
	//LOGI("#***55 add RichText userID: %s", struserid);

	//label->setString(struserid);
	//--------------显示结果--------------------


	LayerColor *logLay = LayerColor::create(Color4B(0x22, 0x11, 0x22, 255));
	logLay->setContentSize(Size(vwtemp * 7.6 / 15, vhtemp * 26.5 / 35));
	logLay->setPosition(Vec2(vwtemp * 7.2 / 15, vhtemp * 3 / 35));
	this->addChild(logLay);


	std::string start_str = "";
	jdisplay = Label::create(start_str, "fonts/arial.ttf", 12);//要显示的内容，字体，字号    
	jdisplay->setTag(100);
	jdisplay->setColor(ccc3(233, 255, 200));  //设置颜色  
	jdisplay->setDimensions(vwtemp * 8 / 15, vhtemp * 27 / 35);
	jdisplay->setPosition(Vec2(vwtemp * 11.2 / 15, vhtemp * 15 / 35));
	this->addChild(jdisplay, 2);

	//----------------按钮------------------


	buttonpay_close = Button::create("9.png", "9.png");
	buttonpay_close->setScale9Enabled(true);
	buttonpay_close->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_close->setTitleFontSize(8);
	buttonpay_close->setPosition(Vec2(vwtemp - buttonpay_close->getContentSize().width / 2, origin.y + buttonpay_close->getContentSize().height / 2));
	buttonpay_close->setTitleText(("关闭"));
	buttonpay_close->setZoomScale(0.4f);
	buttonpay_close->setPressedActionEnabled(true);
	buttonpay_close->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::menuCloseCallback, this));
	this->addChild(buttonpay_close);

	buttonpay_back = Button::create("9.png", "9.png");
	buttonpay_back->setScale9Enabled(true);
	buttonpay_back->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_back->setTitleFontSize(8);
	buttonpay_back->setPosition(Vec2(vwtemp - buttonpay_back->getContentSize().width * 1.6, origin.y + buttonpay_back->getContentSize().height / 2));
	buttonpay_back->setTitleText(("返回"));
	buttonpay_back->setZoomScale(0.4f);
	buttonpay_back->setPressedActionEnabled(true);
	buttonpay_back->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::menuHelloCallback, this));
	this->addChild(buttonpay_back);


	buttonglogin = getButton("animationbuttonnormal.png", "9.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 32 / 35, ("Login Lobby"));
	buttonglogin->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_gameloginCallback, this));
	this->addChild(buttonglogin);

	buttonrin = getButton("2.png", "2.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 27 / 35, ("Enter Room"), false);
	buttonrin->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_roominCallback, this));
	this->addChild(buttonrin);

	buttonready = getButton("3.png", "3.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 22 / 35, ("Ready"), false);
	buttonready->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_readyCallback, this));
	this->addChild(buttonready);

	buttonstart = getButton("4.png", "4.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 17 / 35, ("Start"), false);
	buttonstart->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_startCallback, this));
	this->addChild(buttonstart);

	buttonsrand = getButton("5.png", "5.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 12 / 35, ("Send"), false);
	buttonsrand->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_send_randCallback, this));
	this->addChild(buttonsrand);

	buttonsendreliable = getButton("1.png", "1.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 7 / 35, ("SendReliable)"), false);
	buttonsendreliable->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_send_sreliableCallback, this));
	this->addChild(buttonsendreliable);

	buttongout = getButton("animationbuttonnormal.png", "6.png", \
		vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 32 / 35, ("Logout Lobby"), false);
	buttongout->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_gamelogoutCallback, this));
	this->addChild(buttongout);

	buttonrout = getButton("7.png", "7.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 27 / 35, ("Room Out"), false);
	buttonrout->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_roomoutCallback, this));
	this->addChild(buttonrout);

	buttongover = getButton("8.png", "8.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 17 / 35, ("GameOver"), false);
	buttongover->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_gameoverCallback, this));
	this->addChild(buttongover);

	buttonclear = getButton("1.png", "1.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 5.5 / 15, vhtemp * 7 / 35, ("清除屏幕"), true);
	buttonclear->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoLobbyScene::u_clearCallback, this));
	this->addChild(buttonclear);



	lobby_str = "...";
	m_fomain->set_str(&lobby_str);
	this->scheduleUpdate();
	return true;
}

void MatchVSDemoLobbyScene::update(float dt)   //注意参数类型  
{
	DemoLock();
	jdisplay->setString((lobby_str.c_str()));
	DemoUnlock();

	LockButton();//等待点击按钮的一些操作完成�?

	if (GetNeedUpdateButtonFlag()) {//点击了按钮等待回�?
		if (GetLoginFlag() == false)//未登�?
		{
			buttontrue(buttonglogin); 	buttonfalse(buttongout);
			buttonfalse(buttonrin);		buttonfalse(buttonrout);
			buttonfalse(buttonready);
			buttonfalse(buttonstart);   buttonfalse(buttongover);
			buttonfalse(buttonsrand);
			buttonfalse(buttonsendreliable);
		}
		else//登陆了游�?
		{
			buttonfalse(buttonglogin);
			buttontrue(buttongout);

			if (IsOwner())//房主,房间里仅房主一个人，房主可开始；房间有多个人，必须等到所有人都准备了才能开始�?
			{
				if (GetUserStatus() == UserStatus::STATUS_IN)//用户进入态，第一列只有准备按�?
				{
					buttonfalse(buttonrin);		buttontrue(buttonrout);
					buttontrue(buttonready);
					buttonfalse(buttonstart);   buttonfalse(buttongover);
					buttonfalse(buttonsrand);
					buttonfalse(buttonsendreliable);
				}
				else if (GetUserStatus() == UserStatus::STATUS_READY)//准备�?
				{
					buttonfalse(buttonrin);		buttontrue(buttonrout);
					buttonfalse(buttonready);
					buttonfalse(buttongover);
					buttonfalse(buttonsrand);
					buttonfalse(buttonsendreliable);

					if (GetStartFlag())//房主可以点击按钮�?
						buttontrue(buttonstart);
					else
						buttonfalse(buttonstart);

				}
				else if (GetUserStatus() == UserStatus::STATUS_START)//游戏�?
				{
					buttonfalse(buttonrin);		buttontrue(buttonrout);
					buttonfalse(buttonready);
					buttonfalse(buttonstart);   buttontrue(buttongover);
					buttontrue(buttonsrand);
					buttontrue(buttonsendreliable);

					//Test
					BattleMapManager::getInstance()->SetTeamBornEdge(BornEdgeType::BornEdgeType_Left);
					GameManager::getInstance()->EnterBattleMap(0);
					//end
				}
				else {//不在房间�?			
					buttontrue(buttonrin);		buttonfalse(buttonrout);
					buttonfalse(buttonready);
					buttonfalse(buttonstart);   buttonfalse(buttongover);
					buttonfalse(buttonsrand);
					buttonfalse(buttonsendreliable);
				}
			}
			else//非房�?
			{
				if (GetUserStatus() == UserStatus::STATUS_IN)//用户进入态，第一列只有准备按�?
				{
					buttonfalse(buttonrin);		buttontrue(buttonrout);
					buttontrue(buttonready);
					buttonfalse(buttonstart);   buttonfalse(buttongover);
					buttonfalse(buttonsrand);
					buttonfalse(buttonsendreliable);
				}
				else if (GetUserStatus() == UserStatus::STATUS_READY)//准备�?
				{
					buttonfalse(buttonrin);		buttontrue(buttonrout);
					buttonfalse(buttonready);
					buttonfalse(buttonstart);   buttonfalse(buttongover);
					buttonfalse(buttonsrand);
					buttonfalse(buttonsendreliable);
				}
				else if (GetUserStatus() == UserStatus::STATUS_START)//游戏�?
				{
					buttonfalse(buttonrin);		buttontrue(buttonrout);
					buttonfalse(buttonready);
					buttonfalse(buttonstart);   buttontrue(buttongover);
					buttontrue(buttonsrand);
					buttontrue(buttonsendreliable);

					//Test
					BattleMapManager::getInstance()->SetTeamBornEdge(BornEdgeType::BornEdgeType_Left);
					GameManager::getInstance()->EnterBattleMap(0);
					//end
				}
				else {//不在房间�?			
					buttontrue(buttonrin);		buttonfalse(buttonrout);
					buttonfalse(buttonready);
					buttonfalse(buttonstart);   buttonfalse(buttongover);
					buttonfalse(buttonsrand);
					buttonfalse(buttonsendreliable);
				}
			}
		}
		/*
		//进入房间后根据用户的状态和房主id来确定按�?...............
		//先区分是不是说房�?
		//还可以增加用户状态是否改�?

		*/

		if (HasOwnerChanged())//房主改变
		{
			displayOwnerID();
		}
	}
	UnlockButton();
}
bool MatchVSDemoLobbyScene::displayOwnerID()
{
	int ownerid;
	char  strownerid[25];
	ownerid = GetOwnerID();
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	sprintf_s(strownerid, sizeof(strownerid), "Owner ID:%d", ownerid);
#else // defined(__linux__) || defined(__linux)
	sprintf(strownerid, "Owner ID:%d", ownerid);
#endif

	RichElementText* rn = RichElementText::create(7, Color3B::WHITE, 255, strownerid, "fonts/arial.ttf", 15);
	Textowner->removeElement(0);
	Textowner->pushBackElement(rn);
	return true;
}


void MatchVSDemoLobbyScene::u_gameloginCallback(Ref* pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		LockButton();
		SetNeedUpdateButtonFlag(false);
		buttonfalse(buttonglogin);//避开快速重复点�?
		UnlockButton();
		const char * i = m_fomain->LobbyHandle("gameLogin", 1);

	}
	break;
	default:
		break;
	}
}

void MatchVSDemoLobbyScene::u_roominCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		LockButton();
		SetNeedUpdateButtonFlag(false);
		buttonfalse(buttonrin);
		UnlockButton();
		const char * i = m_fomain->Handle("roomIn");

	}
	break;
	default:
		break;
	}
}

void MatchVSDemoLobbyScene::u_readyCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		LockButton();
		SetNeedUpdateButtonFlag(false);
		buttonfalse(buttonready);
		UnlockButton();
		const char * i = m_fomain->Handle("ready");

	}
	break;
	default:
		break;
	}
}

void MatchVSDemoLobbyScene::u_startCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		LockButton();
		SetNeedUpdateButtonFlag(false);
		buttonfalse(buttonstart);
		UnlockButton();
		const char * i = m_fomain->Handle("start");

	}
	break;
	default:
		break;
	}

	
}
void  MatchVSDemoLobbyScene::u_send_randCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = m_fomain->Handle("send_rand");

	}
	break;
	default:
		break;
	}
}
void  MatchVSDemoLobbyScene::u_send_sreliableCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		const char * i = m_fomain->Handle("send_reliable");
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoLobbyScene::u_gamelogoutCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		LockButton();
		buttonfalse(buttongout);
		SetIsLoginFlag(false);
		ClearALL();
		UnlockButton();
		const char * i = m_fomain->Handle("gameLogout");
		/////////////////////////////KOSetNeedUpdateButton(false);

	}
	break;
	default:
		break;
	}
}
void MatchVSDemoLobbyScene::u_roomoutCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		LockButton();
		SetNeedUpdateButtonFlag(false);
		buttonfalse(buttonrout);
		UnlockButton();
		const char * i = m_fomain->Handle("roomout");

	}
	break;
	default:
		break;
	}
}
void MatchVSDemoLobbyScene::u_gameoverCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		LockButton();
		SetNeedUpdateButtonFlag(false);
		buttonfalse(buttongover);
		UnlockButton();
		const char * i = m_fomain->Handle("gameover");

	}
	break;
	default:
		break;
	}
}
void MatchVSDemoLobbyScene::menuCloseCallback(Ref* pSender, Widget::TouchEventType type)
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
void MatchVSDemoLobbyScene::menuHelloCallback(Ref* pSender, Widget::TouchEventType type)
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
void MatchVSDemoLobbyScene::u_clearCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		DemoLock();
		lobby_str = "...";
		DemoUnlock();
	}
	break;
	default:
		break;
	}
}



void MatchVSDemoLobbyScene::buttontrue(Button* bt)
{
	//bt->setTouchEnabled(true);
	bt->setBright(true);
	bt->setEnabled(true);
	//bt->setColor(Color3B(255, 255, 255));


}
void MatchVSDemoLobbyScene::buttonfalse(Button* bt)
{
	//bt->setTouchEnabled(false);
	bt->setBright(false);
	bt->setEnabled(false);
	//bt->setColor(Color3B(0, 0, 0));
}



void MatchVSDemoLobbyScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}
void MatchVSDemoLobbyScene::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}
void MatchVSDemoLobbyScene::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void MatchVSDemoLobbyScene::editBoxReturn(ui::EditBox* editBox)
{
	log("editBox %p was returned !", editBox);

	std::stringstream ss;
	int c;

	if (_editName == editBox)
	{
		ss << _editName->getText();
		ss >> c;
//		m_fomain->setidandtoken(c);
	}

}
Button* MatchVSDemoLobbyScene::getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str, bool invaild)
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



/*
Button* SceneLobby::getbutton(float w, float h, char const * str, buttonCallback cb)
{
Button* buttontemp = Button::create("animationbuttonnormal.png",
"animationbuttonpressed.png");
buttontemp->setScale9Enabled(true);
buttontemp->setContentSize(Size(90, 20));
buttontemp->setTitleFontSize(8);
buttontemp->setPosition(Vec2(origin.x + buttontemp->getContentSize().width * w, origin.y + jh - buttontemp->getContentSize().height * h));
buttontemp->addTouchEventListener(CC_CALLBACK_2(cb, this));
buttontemp->setTitleText(str);
buttontemp->setZoomScale(0.4f);
buttontemp->setPressedActionEnabled(true);
buttonfalse(buttontemp);
this->addChild(buttontemp);
}

*/