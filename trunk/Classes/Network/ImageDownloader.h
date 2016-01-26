#ifndef __CCIMAGE_DOWNLOADER_H__
#define __CCIMAGE_DOWNLOADER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/HttpClient.h"
#include "ImageNotifyCenter.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace network;

class ImageDownloader : public cocos2d::CCObject
{
   
public:

	virtual bool init();

	void SendHttpRequest(CCObject* pTarget, SEL_FrameNotification pSelector, const char* url, CCNode* node, const char* filename);
	void HttpRequestComplete(HttpClient *sender, HttpResponse *response);

	CREATE_FUNC(ImageDownloader);
public:
	//ID of viewer
	CCString    observerID;
	//download picture load to upper layer
	CCNode*    node;
	//if use picture mask
	bool        useMask;
	//picture file name
	const char* filename;
};

#endif


