#pragma once

#include "MatchVSDemoUserBattle.h"
#include "MatchVSDemoCommon.h"
USING_NS_CC;

int controlpthread = 0;
ms_int32_t  MatchVSDemoUserCallback::onError(ms_int32_t i32Errno)
{
	DemoEcho(hwold, "Errno[%d]\n", i32Errno);
	

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoUserCallback::onGetUserInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int32_t  i32UserID, ms_int8_t *pI8Token, ms_int8_t *pI8NickName, ms_int8_t *pI8Avatar)
{
	if (MATCHVS_OK == i32Status) {
        DemoEcho(hwold, "getuserinfo \nuserid[%d] \n token[%s]\n nickname[%s]\n avatar[%s]\n", i32UserID, pI8Token,pI8NickName, pI8Avatar);
		controlpthread = 1;
		return MATCHVS_OK;
	}
	else {
		
		DemoEcho(hwold, "getuserinfo error[%d] code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_ERROR;
}

ms_int32_t   MatchVSDemoUserCallback::onRegitBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int32_t  i32UserID, ms_int8_t *pI8Token)
{
	if (MATCHVS_OK == i32Status) {
        DemoEcho(hwold, "regit \nuserid[%d] token[%s]\n", i32UserID, pI8Token);
		controlpthread = 1;
		return MATCHVS_OK;
	}
	else {
		DemoEcho(hwold, "regit error[%d] code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_ERROR;
}

ms_int32_t   MatchVSDemoUserCallback::onLoginBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int32_t  i32UserID, ms_int8_t *pI8Token)
{
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "login\nuserid[%d] token[%s]\n", i32UserID, pI8Token);
		controlpthread = 1;
		
		
		CMatchVSUser *uc = CMatchVSUser::getInstance();
		
		const char* cUserToken = pI8Token;
		int ret = uc->getUserID(&i32UserID);
		if (ret == MATCHVS_ERROR)
		{
			// please register first
			
		}

	
		SetUserIDToken(i32UserID, cUserToken);
		
		return MATCHVS_OK;
	}
	else {
		DemoEcho(hwold,  "login error[%d] code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_ERROR;
}




ms_int32_t MatchVSDemoUserCallback::onLoginBackWithInfo(CMatchVSUserInfo *pUserInfo, int errCode)
{

    DemoEcho(hwold, "errCode: %d, userid:%d, token:%s", errCode, pUserInfo->i32UserID, pUserInfo->strToken.pData);
    controlpthread = 1;
    return MATCHVS_OK;


}


ms_int32_t  MatchVSDemoBattleCallback::onError(ms_int32_t i32Errno)
{

	DemoEcho(hwold, "Errno[%d]\n", i32Errno);

	controlpthread = 1;
	return MATCHVS_OK;
}


ms_int32_t  MatchVSDemoBattleCallback::onBattleFieldsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}
	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}
	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onBattleGameInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}
	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onFirstVideoByUserIdArrFriBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);	}

	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onOfficialBuddiesBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "msg[%s]\n", pI8Msg);
	}
	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}
	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onAllDetailBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onBattleGameDetailBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoBattleCallback::onBattleGameFieldsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}


	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onBattleGameProductsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "msg[%s]\n", pI8Msg);
	}


	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onBattleGamesBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}


	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoBattleCallback::onBattleGameVersionsBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "msg[%s]\n", pI8Msg);
	}


	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onDayRankBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Error && MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "%s\n", pI8Data);
		controlpthread = 1;
		return MATCHVS_OK;
	}
	else {
		DemoEcho(hwold,  "onDayRankBack()\n");
		controlpthread = 1;
		return MATCHVS_ERROR;
	}
}


ms_int32_t  MatchVSDemoBattleCallback::onFirstVideoByUserIdArrBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onGameStatusBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onLobbyUserInfoBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onMyRankBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	DemoEcho(hwold, "status[%d]\n", i32Status);
	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onOnLineListBack(ms_int32_t i32Error, ms_int32_t i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Error && MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "%s\n", pI8Data);
		controlpthread = 1;
		return MATCHVS_OK;
	}
	else {
		DemoEcho(hwold, "onOnLineListBack()");

		controlpthread = 1;
		return MATCHVS_ERROR;
	}
}


ms_int32_t  MatchVSDemoBattleCallback::onPopVideoListBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold,  "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoBattleCallback::onPopVideoTagListBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]", pI8Msg);

	}

	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoBattleCallback::onVideoByUserIdBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold,  "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}


	controlpthread = 1;
	return MATCHVS_OK;
}

ms_int32_t MatchVSDemoBattleCallback::onVideoListByTagBack(ms_int32_t i32Error, ms_int32_t  i32Status, ms_int32_t i32Code, ms_int8_t const *pI8Msg, ms_int8_t const *pI8Data)
{
	char buf[1024];
	if (MATCHVS_OK == i32Status) {
		DemoEcho(hwold, "msg[%s]\n", pI8Msg);
	}

	else {
		DemoEcho(hwold, "i32Error[%d] i32Code[%d]\n", i32Error, i32Code);
	}

	controlpthread = 1;
	return MATCHVS_OK;
}













ms_int32_t strkocmp(const char * str1, const char *str2)
{

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	return  _stricmp(str1, str2);
#else // defined(__linux__) || defined(__linux)
	return strcasecmp(str1, str2);
#endif
}



const char * fortestuserbattlemain(char cType, char const *pAct)
{
	MatchVSSetMode(MATCHVS_RUN_MODE_DEBUG);
	controlpthread = 0;
	static std::string tempstr = "";
	static MatchVSDemoUserCallback *ucCB = new MatchVSDemoUserCallback(&tempstr);
	static MatchVSDemoBattleCallback *bcCB = new MatchVSDemoBattleCallback(&tempstr);
	
	ucCB->pI8Mac = "mac";
	ucCB->pI8DeviceID = "123456";
	
	
#if !__MAC__
	char logPath[1024] = {0};
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	strcat(logPath, "D:\\");
#elif __MAC__
    getWritablePath(logPath);
    printf("get wirte path:%s\n", logPath);
    strcat(logPath, "/");
#else // defined(__linux__) || defined(__linux)
    strcat(logPath, "/sdcard/KOGameBox/");
	if (NULL == opendir(logPath))
		mkdir(logPath, 0775);
#endif
    strcat(logPath, "cocos_userbattle_log.txt");
	if (freopen(logPath, "a+", stdout) == NULL)
		fprintf(stderr, "重定向错误！无法输出到文本\n");
	
	
	if (setvbuf(stdout, NULL, _IONBF, 0) != 0)
		printf("failed to set up buffer for output file\n");
	else
		printf("buffer set up for output file\n");
#endif

	
	
	CMatchVSUser *uc = CMatchVSUser::getInstance();
	CMatchVSBattle *bc = CMatchVSBattle::getInstance();
	
	CMatchVSUser::getInstance()->initWithCallback(ucCB);
	CMatchVSBattle::getInstance()->initWithCallback(bcCB);

	switch (cType)
	{
	case 'u':
	case 'U':
	{
		if (!(pAct && strkocmp(pAct, "Register") && strkocmp(pAct, "All"))) {
			if (MATCHVS_OK != CMatchVSUser::isRegister()) {
				if (MATCHVS_OK != uc->userRegit(123456)) {
					printf( "uc->userRegit()\n");
				}
			}
			else
			{
				printf( "have Register\n");
				char buf[102];

				controlpthread = 1;
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
				sprintf_s(buf, sizeof(buf), "have Register");
#else // defined(__linux__) || defined(__linux)
				sprintf(buf, "have Register");
#endif


				tempstr += buf;
				tempstr += '\n';

			}

		}
		//未注�? 初始化不�?
		if (!(pAct && strkocmp(pAct, "Login") && strkocmp(pAct, "All"))) {
			ms_int32_t id = 0;

			if (MATCHVS_OK == uc->getUserID(&id)) {
				printf( "id[%d]\n", id);
			}
			else {
				printf( "uc->getUserID() fail\n");
			}

			if (MATCHVS_OK == uc->login()) {
				printf( "uc->login()\n");
			}
			else {
				printf( "uc->login() failed\n");
			}
		}

		if (!(pAct && strkocmp(pAct, "GetUserInfo") && strkocmp(pAct, "All"))) {

            if (MATCHVS_OK ==
#ifdef WIN32
                uc->getUserInfo()
#else
                uc->login()
#endif
                ) {
				printf( "uc->getUserInfo()\n");
			}
			else {
				printf( "uc->getUserInfo()\n");
			}
		}

		if (!(pAct && strkocmp(pAct, "ChangeUserInfo") && strkocmp(pAct, "All"))) {
			if (MATCHVS_OK == uc->changeUserInfo("zhong", "Avatar2")) {
				//sleep(5);
				printf( "uc->changeUserInfo()\n");
			}
			else {
				printf( "uc->changeUserInfo()\n");
			}
		}
		break;
	}
	case 'b':
	case 'B':
	{
#if 1
		bc->setGameInfo(100011, 1);//100011  100926  //-- 1   2   

		if (!(pAct && strkocmp(pAct, "GetBattleFields") && strkocmp(pAct, "All") && strkocmp(pAct, "go"))) {//ok
			if (MATCHVS_OK == bc->getBattleFields()) {
				printf( "bc->GetBattleFields()\n");
			}
			else {
				printf( "bc->GetBattleFields()\n");
			}
		}

		//--end
		if (!(pAct && strkocmp(pAct, "getAllDetail") && strkocmp(pAct, "All") && strkocmp(pAct, "goo"))) {//  正确的token值会导致free()失败的致命错�?
			if (MATCHVS_OK == bc->getAllDetail()) {
				printf( "bc->getAllDetail()\n");
			}
			else {
				printf( "bc->getAllDetail()\n");
			}
		}
		if (!(pAct && strkocmp(pAct, "getBattleGameDetail") && strkocmp(pAct, "All") && strkocmp(pAct, "go"))) {//404
			ms_int32_t                  userids[] = { 101,102 };
			ms_int32_t                  num;
			num = 2;
			if (MATCHVS_OK == bc->getBattleGameDetail(userids, num)) {
				printf( "bc->getBattleGameDetail()\n");
			}
			else {
				printf( "bc->getBattleGameDetail()\n");
			}
		}
		if (!(pAct && strkocmp(pAct, "getBattleGameFields") && strkocmp(pAct, "All") && strkocmp(pAct, "go"))) {//404
			if (MATCHVS_OK == bc->getBattleGameFields(1, 1)) {
				printf( "bc->method()\n");
			}
			else {
				printf( "bc->method()\n");
			}
		}


		if (!(pAct && strkocmp(pAct, "GetDayRank") && strkocmp(pAct, "All"))) {

			if (MATCHVS_OK == bc->getDayRank()) {
				printf( "bc->method()\n");
			}
			else {
				printf( "bc->method()\n");
			}

		}

		if (!(pAct && strkocmp(pAct, "getLobbyUserInfo") && strkocmp(pAct, "All"))) {
			ms_int32_t                  userids[] = { 101,102 };
			ms_int32_t                  num;
			num = 2;
			if (MATCHVS_OK == bc->getLobbyUserInfo(userids, num)) {
				printf( "bc->method()\n");
			}
			else {
				printf( "bc->method()\n");
			}
		}
		if (!(pAct && strkocmp(pAct, "GetMyRank") && strkocmp(pAct, "All"))) {
			if (MATCHVS_OK == bc->getMyRank()) {
				printf( "bc->method()\n");
			}
			else {
				printf( "bc->method()\n");
			}
		}

		if (!(pAct && strkocmp(pAct, "GetOnlineList") && strkocmp(pAct, "All"))) {
			if (MATCHVS_OK == bc->getOnLineList()) {
				printf( "bc->method()\n");
			}
			else {
				printf( "bc->method()\n");
			}
		}


#endif
		break;
	}
	default:
		printf("Unknown type[%c]\n", cType);
		break;
	}

	int fori = 0;
	while (1)
	{
		if (controlpthread == 1)break;
		if (++fori > 500000000)break;
	}

	return tempstr.c_str();
}