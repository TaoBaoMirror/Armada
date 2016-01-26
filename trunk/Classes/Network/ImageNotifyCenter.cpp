#include "ImageNotifyCenter.h"

ImageNotifyCenter* ImageNotifyCenter::sharedImageNotificationCenter(void)
{
	static ImageNotifyCenter imageNotificationCenter;
	return &imageNotificationCenter;
}

CCString ImageNotifyCenter::addObserver(const char *imageName, CCNode* node, bool useMask)
{
	CCString* observerIDstr = CCString::createWithFormat("%d", m_observerID);

	m_notificationCenter.addObserver(this, callfuncO_selector(ImageNotifyCenter::imageLoaded), observerIDstr->getCString(),
		new imgstruct(imageName, observerIDstr->getCString(), node, useMask));

	m_observerID++;
	return observerIDstr->getCString();
}

void ImageNotifyCenter::removeObserver(const char *name)
{
	m_notificationCenter.removeObserver(this, name);
}

void ImageNotifyCenter::postNotification(const char *name, CCObject *object)
{
	m_notificationCenter.postNotification(name, object);
}

void ImageNotifyCenter::imageLoaded(CCObject *obj)
{
	imgstruct* img = (imgstruct*)obj;
	//CCLOG("imageLoaded success,imageName:%s",img->imageName.c_str());
	CCSpriteFrame* spriteFrame = ImageNotifyCenter::getSpriteFromWriteablePath(img->imageName.c_str());
	//CCLOG("got sprite 0x%X", sprite);
	if (img->useMask)
	{
		//img->node->addChild(CCImageNotificationCenter::createMaskedSprite(sprite, "mask.png"));
	}
	else
	{
		/*float scale_ = (float)img->node->getContentSize().width / (float)sprite->getContentSize().width;
		sprite->setAnchorPoint(ccp(0.5f, 0.5f));
		img->node->addChild(sprite);*/
	}
	this->removeObserver(img->observerId.c_str());

	(m_ImageNotificationTarget->*m_pImageNotificationSelector)(img->node, spriteFrame);
	
	img->release();
}


CCSpriteFrame* ImageNotifyCenter::getSpriteFromWriteablePath(const char* name)
{
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path += name;
	FILE* fp = fopen(path.c_str(), "rb");
	if (!fp)
	{
		return NULL;
	}
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buf = (char*)malloc(len);
	fread(buf, len, 1, fp);
	fclose(fp);

	CCImage* img = new CCImage;
   
	img->initWithImageData((const unsigned char*)buf, len);
	free(buf);
	cocos2d::CCTexture2D* texture = new cocos2d::CCTexture2D();
	bool isImg = texture->initWithImage(img);
	img->release();
	if (!isImg)
	{
		delete texture;
		return NULL;
		//return CCSprite::create("default.png");//加载资源并非图片时返回的默认图
	}

	CCSprite* sprite = CCSprite::createWithTexture(texture);
	float sWidth = sprite->getContentSize().width;
	float sHeight = sprite->getContentSize().height;
	CCSpriteFrame* callBackFrame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0,0,sWidth,sHeight));
	texture->release();
	return callBackFrame;
}


CCSprite* ImageNotifyCenter::createMaskedSprite(CCSprite* src, const char* maskFile)
{
	//�������� ���Ļ�����ԭ��ο���//http://blog.csdn.net/azymq/article/details/11110019

	CCSprite * mask = CCSprite::create(maskFile);

	assert(src);
	assert(mask);

	CCSize srcContent = src->getContentSize();
	CCSize maskContent = mask->getContentSize();

	CCRenderTexture * rt = CCRenderTexture::create(srcContent.width, srcContent.height, Texture2D::PixelFormat::RGBA8888);

	float ratiow = srcContent.width / maskContent.width;
	float ratioh = srcContent.height / maskContent.height;
	mask->setScaleX(ratiow);
	mask->setScaleY(ratioh);

	mask->setPosition(ccp(srcContent.width / 2, srcContent.height / 2));
	src->setPosition(ccp(srcContent.width / 2, srcContent.height / 2));

	ccBlendFunc blendFunc2 = { GL_ONE, GL_ZERO };
	mask->setBlendFunc(blendFunc2);
	ccBlendFunc blendFunc3 = { GL_DST_ALPHA, GL_ZERO };
	src->setBlendFunc(blendFunc3);

	rt->begin();
	mask->visit();
	src->visit();
	rt->end();

	CCSprite * retval = CCSprite::createWithTexture(rt->getSprite()->getTexture());
	retval->setFlipY(true);

	return retval;
}