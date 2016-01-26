#ifndef __KO_COMMON__H__
#define __KO_COMMON__H__

#include <stdio.h>
#ifndef WIN32
#include <pthread.h>
#endif//
#include <string>

enum UserStatus
{
	STATUS_UNKONW = -1,
	STATUS_IN = 0,
	STATUS_READY = 1,
	STATUS_START = 2
};

void 	DemoEcho(std::string *hwold, char *fmt, ...);


////#ifdef __cplusplus 
////using namespace std;
////#endif
//
//#define LOG_TAG "MatchVS-C"
//#define LOG_TEST_TAG "MatchVSBattleManager-x"
//
//#ifdef LOGABLE
//#if defined(ANDROID)
//#include <android/log.h>
//#define LOGI(message, ...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#define LOGW(message, ...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#define LOGE(message, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#define LOGF(message, ...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#elif (defined(WIN32) || defined(WIN64) || defined(_WINDOWS_))
//#define LOGI(message, ...) printf(ANDROID_LOG_INFO, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#define LOGW(message, ...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#define LOGE(message, ...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#define LOGF(message, ...) __android_log_print(ANDROID_LOG_FATAL, LOG_TAG, "%s: " message, __FUNCTION__, ##__VA_ARGS__)
//#endif//


void	ClearALL();
void	ClearRoomOut();

bool    SetUserIDToken(const int userid, const  char *token);
int     GetUserID();
bool    GetUserToken(char *token);
bool    HaveSetUserToken();

bool	SetRoomOwner(const int ownerid);
bool	IsOwner();
int		GetOwnerID();
bool	HasOwnerChanged();

bool	SetUserStatus(UserStatus userstatus);
UserStatus		GetUserStatus();


//登陆
void	SetIsLoginFlag(bool tf);
bool	GetLoginFlag();

//房主能否点击开�?
void	SetStartFlag(bool tf);
bool	GetStartFlag();


//点击后等待返�?
void	SetNeedUpdateButtonFlag(bool tf);
bool	GetNeedUpdateButtonFlag();

//锁按�?
void LockButton();
void UnlockButton();
void DemoLock();
void DemoUnlock();




#endif
