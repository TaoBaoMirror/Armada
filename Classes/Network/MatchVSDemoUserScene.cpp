#include "MatchVSDemoUserScene.h"
#include "ImageDownloader.h"
Scene* MatchVSDemoUserScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MatchVSDemoUserScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MatchVSDemoUserScene::init()
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


	std::string start_str = "display";
	jdisplay = Label::create(start_str, "fonts/arial.ttf", 12);//要显示的内容，字体，字号
	jdisplay->setTag(100);
	jdisplay->setColor(ccc3(0, 255, 0));  //设置颜色  
	jdisplay->setLineBreakWithoutSpace(true);
	jdisplay->setDimensions(vwtemp / 4 * 2, vhtemp * 0.8);
	jdisplay->setPosition(Vec2(vwtemp * 0.55, vhtemp * 0.5));
	//this->addChild(jdisplay, 2);

	LayerColor *logLay = LayerColor::create(Color4B(0x22, 0x11, 0x22, 255));
	logLay->setContentSize(Size(vwtemp * 10.6 / 15, vhtemp * 32 / 35));
	logLay->setPosition(Vec2(vwtemp * 4 / 15, vhtemp * 2.5 / 35));
	this->addChild(logLay);



    RichText *richLabelUserID = RichText::create();
    richLabelUserID->ignoreContentAdaptWithSize(false);
    richLabelUserID->setContentSize(Size(50, 30));
    richLabelUserID->setPosition(Vec2(vwtemp * 0.32, vhtemp * 0.93));
    richLabelUserID->setLocalZOrder(10);
    this->addChild(richLabelUserID);
    RichElementText* retLL = RichElementText::create(7, Color3B::ORANGE, 255, ("UserID:"), "fonts/arial.ttf", 10);
    richLabelUserID->pushBackElement(retLL);


    RichText *richLabelNickName = RichText::create();
    richLabelNickName->ignoreContentAdaptWithSize(false);
    richLabelNickName->setContentSize(Size(50, 30));
    richLabelNickName->setPosition(Vec2(vwtemp * 0.5, vhtemp * 0.93));
    richLabelNickName->setLocalZOrder(10);
    this->addChild(richLabelNickName);
    RichElementText* retLN = RichElementText::create(7, Color3B::ORANGE, 255, ("Nick:"), "fonts/arial.ttf", 10);
    richLabelNickName->pushBackElement(retLN);





	RichElementText* rt1 = RichElementText::create(7, Color3B::ORANGE, 255, "", "fonts/arial.ttf", 10);
    _richText = RichText::create();
	_richText->ignoreContentAdaptWithSize(false);
	_richText->setContentSize(Size(200, 100));
	_richText->setPosition(Vec2(vwtemp * 0.5, vhtemp * 0.7));
	_richText->pushBackElement(rt1);
	_richText->setLocalZOrder(10);
	this->addChild(_richText);


	RichElementText* rt2 = RichElementText::create(7, Color3B::ORANGE, 255, "", "fonts/arial.ttf", 10);
    _richUserID = RichText::create();
    _richUserID->ignoreContentAdaptWithSize(false);
    _richUserID->setContentSize(Size(50, 30));
    _richUserID->setPosition(Vec2(vwtemp * 0.32, vhtemp * 0.9));
	_richUserID->pushBackElement(rt2);
    _richUserID->setLocalZOrder(10);
    this->addChild(_richUserID);


	RichElementText* rt3 = RichElementText::create(7, Color3B::ORANGE, 255, "", "fonts/arial.ttf", 10);
    _richNickName = RichText::create();
    _richNickName->ignoreContentAdaptWithSize(false);
    _richNickName->setContentSize(Size(50, 30));
    _richNickName->setPosition(Vec2(vwtemp * 0.5, vhtemp * 0.9));
    _richNickName->setLocalZOrder(10);
	_richNickName->pushBackElement(rt3);
    this->addChild(_richNickName);



    _avatarNode = CCNode::create();
    _avatarNode->setContentSize(Size(80, 80));
    _avatarNode->setPosition(Vec2(vwtemp * 0.7, vhtemp * 0.9));
    _avatarNode->setLocalZOrder(10);
    this->addChild(_avatarNode);

	//----------------按钮------------------



	buttonpay_close = Button::create("9.png", "9.png");
	buttonpay_close->setScale9Enabled(true);
	buttonpay_close->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_close->setTitleFontSize(8);
	buttonpay_close->setPosition(Vec2(vwtemp - buttonpay_close->getContentSize().width / 2, origin.y + buttonpay_close->getContentSize().height / 2));
	buttonpay_close->setTitleText(("关闭"));
	buttonpay_close->setZoomScale(0.4f);
	buttonpay_close->setPressedActionEnabled(true);
	buttonpay_close->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoUserScene::menuCloseCallback, this));
	this->addChild(buttonpay_close);

	buttonpay_back = Button::create("9.png", "9.png");
	buttonpay_back->setScale9Enabled(true);
	buttonpay_back->setContentSize(Size(vwtemp / 15, vhtemp * 10 / 150));
	buttonpay_back->setTitleFontSize(8);
	buttonpay_back->setPosition(Vec2(vwtemp - buttonpay_back->getContentSize().width * 1.6, origin.y + buttonpay_back->getContentSize().height / 2));
	buttonpay_back->setTitleText(("返回"));
	buttonpay_back->setZoomScale(0.4f);
	buttonpay_back->setPressedActionEnabled(true);
	buttonpay_back->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoUserScene::menuHelloCallback, this));
	this->addChild(buttonpay_back);


#if !(defined(__ANDROID__)||defined(__linux__))
	buttonbgf = getButton("1.png", "1.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 32 / 35, ("注册(userRegit)"));
	buttonbgf->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoUserScene::u_registerCallback, this));
	this->addChild(buttonbgf);
#endif

	buttonbf = getButton("2.png", "2.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 27 / 35, ("登录(login)"));
	buttonbf->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoUserScene::u_logingCallback, this));
	this->addChild(buttonbf);

	buttonad = getButton("3.png", "3.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 22 / 35, ("获取信息(getUserInfo)"), true);
	buttonad->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoUserScene::u_getuserinfoCallback, this));
	this->addChild(buttonad);

	buttonbgd = getButton("4.png", "4.png", vwtemp * 3 / 15, vhtemp * 4 / 35, vwtemp * 2 / 15, vhtemp * 17 / 35, ("改变信息(changeUserInfo)"), false);
	buttonbgd->addTouchEventListener(CC_CALLBACK_2(MatchVSDemoUserScene::u_changeuserinfoCallback, this));
	this->addChild(buttonbgd);


#if !(__MAC__ ||  (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) ) 
    CMatchVSUser::getInstance()->initWithCallback(this);
#endif
	return true;
}


void MatchVSDemoUserScene::menuCloseCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->end();
#if (defined(__linux__) || defined(__linux) )
		exit(0);
#endif
	}
	break;
	default:
		break;
}
}
void MatchVSDemoUserScene::menuHelloCallback(Ref* pSender, Widget::TouchEventType type)
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

void MatchVSDemoUserScene::u_registerCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
#if (__MAC__ ||  (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) )
		const char * i = fortestuserbattlemain('u', "Register");
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
#else
        CMatchVSUser0::getInstance()->userRegit();
#endif
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoUserScene::u_logingCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
#if (__MAC__ ||  (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) )
		const char * i = fortestuserbattlemain('u', "Login");
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
#else
        CMatchVSUser::getInstance()->login();
#endif
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoUserScene::u_getuserinfoCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
#if (__MAC__ ||  (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) )
		const char * i = fortestuserbattlemain('u', "GetUserInfo");
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
#else
        CMatchVSUser::getInstance()->getUserInfo();
#endif
	}
	break;
	default:
		break;
	}
}
void MatchVSDemoUserScene::u_changeuserinfoCallback(Ref* pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
#if (__MAC__ ||  (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) )
		const char * i = fortestuserbattlemain('u', "ChangeUserInfo");
		RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, i, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
#else
		CMatchVSUser::getInstance()->changeUserInfo("test", "http://www.baidu.com/img/bd_logo1.png");
#endif
	}
	break;
	default:
		break;
	}
}

void MatchVSDemoUserScene::buttontrue(Button* bt)
{

	bt->setBright(true);
	bt->setEnabled(true);
}
void MatchVSDemoUserScene::buttonfalse(Button* bt)
{
	bt->setBright(false);
	bt->setEnabled(false);

}
Button* MatchVSDemoUserScene::getButton(const char * filepath1, const char * filepath2, float csw, float csh, float posw, float posh, const char *str, bool invaild )
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


ms_int32_t  MatchVSDemoUserScene::onError(ms_int32_t i32Errno)
{

    printf( "Errno[%d]", i32Errno);
    char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
    sprintf_s(buf, sizeof(buf), "Errno[%d]", i32Errno);
#else // defined(__linux__) || defined(__linux)			
    sprintf(buf, "Errno[%d]", i32Errno);
#endif

    const char* convBuf = (buf);
    RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
    _richText->removeElement(0);
    _richText->pushBackElement(re);
   
    return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoUserScene::onGetUserInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
    if (MATCHVS_OK == i32Status) {
        printf( "msg[%s] data[%s]", pI8Msg, pI8Data);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "msg[%s] data[%s]", pI8Msg, pI8Data);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "msg[%s] data[%s]", pI8Msg, pI8Data);
#endif
        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
        return MATCHVS_OK;
    }
    else {
        printf( "i32Error[%d] i32Code[%d]", i32Error, i32Code);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "i32Error[%d] i32Code[%d]", i32Error, i32Code);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "i32Error[%d] i32Code[%d]", i32Error, i32Code);
#endif

        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
    }

    return MATCHVS_ERROR;
}

ms_int32_t   MatchVSDemoUserScene::onRegitBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
    if (MATCHVS_OK == i32Status) {
        printf( "msg[%s] data[%s]", pI8Msg, pI8Data);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "msg[%s] data[%s]", pI8Msg, pI8Data);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "msg[%s] data[%s]", pI8Msg, pI8Data);
#endif
        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);
        return MATCHVS_OK;
    }
    else {
        printf( "i32Error[%d] i32Code[%d]", i32Error, i32Code);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "i32Error[%d] i32Code[%d]", i32Error, i32Code);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "i32Error[%d] i32Code[%d]", i32Error, i32Code);
#endif
        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		_richText->removeElement(0);
		_richText->pushBackElement(re);

    }


    return MATCHVS_ERROR;
}

ms_int32_t   MatchVSDemoUserScene::onLoginBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
    if (MATCHVS_OK == i32Status) {
        printf( "msg[%s] data[%s]", pI8Msg, pI8Data);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "msg[%s] data[%s]", pI8Msg, pI8Data);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "msg[%s] data[%s]", pI8Msg, pI8Data);
#endif
        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		
		_richUserID->removeElement(0);
		_richUserID->pushBackElement(re);
		
        return MATCHVS_OK;
    }
    else {
        printf( "i32Error[%d] i32Code[%d]", i32Error, i32Code);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "i32Error[%d] i32Code[%d]", i32Error, i32Code);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "i32Error[%d] i32Code[%d]", i32Error, i32Code);
#endif

        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		
		_richUserID->removeElement(0);
		_richUserID->pushBackElement(re);
    }

    
    return MATCHVS_ERROR;
}

ms_int32_t  MatchVSDemoUserScene::onChangeUserInfoBack(ms_int32_t i32Error, ms_int32_t i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
    if (MATCHVS_OK == i32Status) {
        printf( "success msg[%s] data[%s]", pI8Msg, pI8Data);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "success msg[%s] data[%s]", pI8Msg, pI8Data);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "success msg[%s] data[%s]", pI8Msg, pI8Data);
#endif
        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		
		_richUserID->removeElement(0);
		_richUserID->pushBackElement(re);
		return MATCHVS_OK;
    }
    else {
        printf( "failed i32Error[%d] i32Code[%d]", i32Error, i32Code);
        char buf[1024];
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
        sprintf_s(buf, sizeof(buf), "failed i32Error[%d] i32Code[%d]", i32Error, i32Code);
#else // defined(__linux__) || defined(__linux)
        sprintf(buf, "failed i32Error[%d] i32Code[%d]", i32Error, i32Code);
#endif
        const char* convBuf = (buf);
        RichElementText* re = RichElementText::create(7, Color3B::ORANGE, 255, convBuf, "fonts/arial.ttf", 10);
		
		_richUserID->removeElement(0);
		_richUserID->pushBackElement(re);
    }

   
    return MATCHVS_ERROR;
}



ms_int32_t MatchVSDemoUserScene::onLoginBackWithInfo(CMatchVSUserInfo *pUserInfo, int errCode)
{

    printf( "userid:%d, token:%s", pUserInfo->i32UserID, pUserInfo->strToken.pData);
    char buf[1024];


  //  m_strNickName = (pUserInfo->strNickName.pData, pUserInfo->strNickName.i32Size);
    m_strNickName = pUserInfo->strNickName.pData;
    m_strAvatar =std::string("head url:") + pUserInfo->strAvatar.pData + "\n\n";
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
    sprintf_s(buf, sizeof(buf), "%d", pUserInfo->i32UserID);
#else // defined(__linux__) || defined(__linux)
    sprintf(buf, "%d", pUserInfo->i32UserID);
#endif
    m_strUserID = buf;
    m_strToken = m_strAvatar + std::string("token:") + pUserInfo->strToken.pData;
    RichElementText* rn = RichElementText::create(7, Color3B::ORANGE, 255, m_strNickName, "fonts/arial.ttf", 10);
 //   RichElementText* ra = RichElementText::create(7, Color3B::ORANGE, 255, m_strAvatar, "fonts/arial.ttf", 10);
    RichElementText* ru = RichElementText::create(7, Color3B::ORANGE, 255, m_strUserID, "fonts/arial.ttf", 10);
    RichElementText* rt = RichElementText::create(7, Color3B::ORANGE, 255, m_strToken, "fonts/arial.ttf", 10);


	_richText->removeElement(0);
    _richText->pushBackElement(rt);

	_richNickName->removeElement(0);
    _richNickName->pushBackElement(rn);

	_richUserID->removeElement(0);
    _richUserID->pushBackElement(ru);


	SetUserIDToken(pUserInfo->i32UserID, pUserInfo->strToken.pData);


    if (pUserInfo->strAvatar.i32Size > 0) {
        //CCImageDownloader *di = CCImageDownloader::create();
       // di->SendHttpRequest(this, framecallfunc_selector(SceneUser::whenImageDownLoad), pUserInfo->strAvatar.pData, _avatarNode, "item.jpg");
    }
    return MATCHVS_OK;


}

void MatchVSDemoUserScene::whenImageDownLoad(CCNode* srcNode, CCSpriteFrame* downFrame)
{
    printf( "whenImageDownLoad begin");
    if (srcNode == NULL || downFrame == NULL)  
        return;
    CCSprite* srcSprite = (CCSprite*)srcNode;
    CCSize srcSize = srcSprite->getContentSize();
    srcSprite->setDisplayFrame(downFrame);
    CCSize curSize = srcSprite->getContentSize();
    float scaleX = srcSize.width / curSize.width;
    float scaleY = srcSize.height / curSize.height;
    srcSprite->setScaleX(scaleX);
    srcSprite->setScaleY(scaleY);

    printf( "whenImageDownLoad end");
}