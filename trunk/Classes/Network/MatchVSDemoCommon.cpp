#include "MatchVSDemoCommon.h"
#include "string.h"
#include "stdio.h"
#include "CommonMutex.h"



CommonMutex s_ButtonLocker;
CommonMutex s_Locker;

static int  s_UserID = 0;
static char s_Token[128] = { 0 };////存储token
static int  s_SetFlag = 0;


static int s_OwnerID = 0;
static int s_OwnerChange = 0;//房主有改�?

UserStatus s_UserStatus = STATUS_UNKONW;
bool s_isLogin = false;//false是未登陆,true登陆
bool s_bOwnerCanStart = false;//房主是否可以点击开�?
bool s_bClickBack = 0;

void ClearALL()
{
	 s_OwnerID = 0;
	 s_OwnerChange = 0;
	 s_UserStatus = STATUS_UNKONW;
	 s_isLogin = false;
	 s_bOwnerCanStart = false;

}
void ClearRoomOut()
{

	s_OwnerID = 0;
	s_OwnerChange = 0;
	s_UserStatus = STATUS_UNKONW;
	s_bOwnerCanStart = false;

}

bool      SetUserIDToken(const int userid, const  char *token)
{
	if (strlen(token) > sizeof(s_Token))
		return false;

	s_UserID = userid;
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	sprintf_s(s_Token, strlen(token) + 1, "%s", token);
#else // defined(__linux__) || defined(__linux)
	sprintf(s_Token, "%s", token);
#endif
	s_SetFlag = 1;

	return  true;
}

int  GetUserID()
{
	return s_UserID;
}

bool  GetUserToken(char *token)
{
	if (strlen(s_Token) == 0)
		return false;

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	sprintf_s(token, strlen(s_Token)+1, "%s", s_Token);
#else // defined(__linux__) || defined(__linux)
	sprintf(token, "%s", s_Token);
#endif
	return  true;

}

bool   HaveSetUserToken()
{
	if (s_SetFlag == 1)
		return true;
	return false;
}

bool	SetRoomOwner(const int ownerid)
{
	s_OwnerID = ownerid;
	s_OwnerChange = 1;
	return 1;
}
bool	IsOwner()
{
	if (s_OwnerID == s_UserID)
		return true;
	return false;
}
int		GetOwnerID()
{
	return s_OwnerID;
}

bool	HasOwnerChanged()
{
	if (s_OwnerChange == 1) {
		s_OwnerChange = 0;
		return true;
	}
	return false;

}

bool SetUserStatus(const UserStatus userstatus)
{
	s_UserStatus = userstatus;
	return true;
}

UserStatus GetUserStatus()
{
	return s_UserStatus;
}

//

void	SetIsLoginFlag(bool isLogin)
{
	s_isLogin = isLogin;
}
bool	GetLoginFlag()
{
	return s_isLogin;
}

//
void	SetStartFlag(bool canStart)
{
	s_bOwnerCanStart = canStart;
}
bool	GetStartFlag()
{
	return s_bOwnerCanStart;
}

//
void	SetNeedUpdateButtonFlag(bool tf)
{
	s_bClickBack = tf;
}
bool	GetNeedUpdateButtonFlag()
{
	return s_bClickBack;
}

void LockButton()
{
	s_ButtonLocker.lock();
}
void UnlockButton()
{
	s_ButtonLocker.unlock();
}


void DemoLock()
{
	s_Locker.lock();
}
void DemoUnlock()
{
	s_Locker.unlock();
}



void DemoEcho(std::string *hwold, char *fmt, ...)
{
	va_list args;
	static char* echobuf = new char[1024];
	va_start(args, fmt);
	
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	vsprintf_s(echobuf, 1024, fmt, args);
#else // defined(__linux__) || defined(__linux)
	vsprintf(echobuf, fmt, args);
#endif
	
	va_end(args);
	
	printf("%s\n", echobuf);
	s_Locker.lock();
	(*hwold) = std::string(echobuf) + "\n" + (*hwold);
	s_Locker.unlock();
}
