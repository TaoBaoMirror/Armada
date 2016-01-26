#include "ImageDownloader.h"
bool ImageDownloader::init()
{
	useMask = false;
	return true;
}

void ImageDownloader::SendHttpRequest(CCObject* pTarget, SEL_FrameNotification pSelector, const char* url, CCNode* node, const char* filename)
{
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	path += filename;
	bool fileIsExist = CCFileUtils::sharedFileUtils()->isFileExist(CCFileUtils::sharedFileUtils()->fullPathForFilename(path.c_str()));
	ImageNotifyCenter::sharedImageNotificationCenter()->m_ImageNotificationTarget = pTarget;
	ImageNotifyCenter::sharedImageNotificationCenter()->m_pImageNotificationSelector = pSelector;
	this->node = node;
	this->filename = filename;
	this->observerID = ImageNotifyCenter::sharedImageNotificationCenter()->addObserver(filename, node, useMask);
	if (fileIsExist || node == NULL)
	{
		ImageNotifyCenter::sharedImageNotificationCenter()->postNotification(this->observerID.getCString(), NULL);
		return;
	}
	HttpRequest* request = new HttpRequest();
	request->setUrl(url);
    request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(ImageDownloader::HttpRequestComplete));
	request->setTag("GET IMAGE");
	HttpClient::getInstance()->send(request);
	request->release();
}

void ImageDownloader::HttpRequestComplete(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}


	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		//CCLog("%s completed", response->getHttpRequest()->getTag());
	}

	int statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
	//CCLog("response code: %d", statusCode);

	if (!response->isSucceed())
	{
		//CCLog("response failed");
		//CCLog("error buffer: %s", response->getErrorBuffer());
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	std::string path = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string bufffff(buffer->begin(), buffer->end());

	path += this->filename;
	CCLOG("path: %s",path.c_str());
	FILE *fp = fopen(path.c_str(), "wb+");
	fwrite(bufffff.c_str(), 1, buffer->size(), fp);
	fclose(fp);
	ImageNotifyCenter::sharedImageNotificationCenter()->postNotification(this->observerID.getCString(), NULL);
}