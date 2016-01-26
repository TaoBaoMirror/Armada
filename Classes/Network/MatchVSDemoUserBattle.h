#ifndef __FORTESTUSERBATTLE_SCENE_H__
#define __FORTESTUSERBATTLE_SCENE_H__


#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))

#else // defined(__linux__) || defined(__linux)
//#includ<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstddef>
#include <string.h>
#include <stdlib.h>
#endif


#include <stdio.h>
#include "MatchVSBase.h"
//#include "KOBack.h"
//#include "ko_base.h"
#include "MatchVSUser.h"
#include "MatchVSBattle.h"
#include "cocos2d.h"
#include "MatchVSDemoScence.h"
USING_NS_CC;

#define JSON_DLL 1




ms_int32_t strkocmp(const char * str1, const char *str2);

class MatchVSDemoUserCallback : public CMatchVSUserCallback
{
public:
	MatchVSDemoUserCallback(std::string *h) :hwold(h) {}
	~MatchVSDemoUserCallback() {}
	std::string *hwold;
	
	ms_int32_t  onError(ms_int32_t i32Errno);
    ms_int32_t onGetUserInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int32_t  i32UserID, ms_int8_t *pI8Token, ms_int8_t *pI8NickName, ms_int8_t *pI8Avatar);
	ms_int32_t  onRegitBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int32_t  i32UserID, ms_int8_t *pI8Token);
	ms_int32_t  onLoginBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int32_t  i32UserID, ms_int8_t *pI8Token);
    ms_int32_t onLoginBackWithInfo(CMatchVSUserInfo *pUserInfo, int errCode);
};

class MatchVSDemoBattleCallback : public CMatchVSBattleCallback
{
public:

	MatchVSDemoBattleCallback(std::string  *h) :hwold(h) {}
	~MatchVSDemoBattleCallback() {}
	std::string *hwold;

	ms_int32_t  onError(ms_int32_t i32Errno);
	ms_int32_t onBattleFieldsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onBattleGameInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onFirstVideoByUserIdArrFriBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onOfficialBuddiesBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onAllDetailBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onBattleGameDetailBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onBattleGameFieldsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onBattleGameProductsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onBattleGamesBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onBattleGameVersionsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onDayRankBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onFirstVideoByUserIdArrBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onGameStatusBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onLobbyUserInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onMyRankBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onOnLineListBack(ms_int32_t i32Error, ms_int32_t i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onPopVideoListBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);

	ms_int32_t onPopVideoTagListBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onVideoByUserIdBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);
	ms_int32_t onVideoListByTagBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data);

};


const char * fortestuserbattlemain(char cType, char const *pAct);



#endif
