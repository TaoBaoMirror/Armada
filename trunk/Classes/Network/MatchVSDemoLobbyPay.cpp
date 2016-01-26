#pragma once

#include "MatchVSDemoLobbyPay.h"
#include "BattleMap\BattleMapManager.h"
#include "GameManager\GameManager.h"



//ms_int32_t  					i32DevelopID;			 //开发者ID
//ms_int32_t 						i32GameID;			   //游戏ID
//ms_int32_t 						i32VersionGame;		  //SDK版本
//ms_int32_t 						i32VersionSDK;		  //游戏版本
//
//ms_str_t					   *pStrDeviceID;			 //设备ID
//ms_str_t  					   *pStrSignature;			 //App fingerprint MD5(签名)
//ms_str_t					   *pStrPackageName;		 //Package Name

int recv_num = 0;



int MatchVSDemoLobbyCallback::i = 0;
ms_str_t    g_pDeviceID = { 2, "12" };
ms_str_t    g_pStrSignature = { 2, "12" };
ms_str_t    g_pStrPackageName = { 2, "12" };



MatchVSDemoLobbyPayBundle *  MatchVSDemoLobbyPayBundle::single = NULL;
MatchVSDemoLobbyPayBundle *  MatchVSDemoLobbyPayBundle::getInstance()
{
	if (single == NULL) {
		single = new MatchVSDemoLobbyPayBundle;
	}
	return single;
}
void MatchVSDemoLobbyPayBundle::release()
{
	if (single != NULL) {
		delete single;
		single = NULL;
	}
}

ms_int32_t MatchVSDemoLobbyPayBundle::strkocmp(const char * str1, const char *str2)
{

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	return  _stricmp(str1, str2);
#else // defined(__linux__) || defined(__linux)
	return strcasecmp(str1, str2);
#endif
}


MatchVSDemoLobbyPayBundle::MatchVSDemoLobbyPayBundle()
{

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* WinSock DLL.                                  */

	}

#endif

#if !__MAC__
	char logPath[1024] = { 0 };
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	strcat(logPath, "D:\\");
//#elif __MAC__
//	getWritablePath(logPath);
//	printf("get wirte path:%s\n", logPath);
//	strcat(logPath, "/");
#else // defined(__linux__) || defined(__linux)
	strcat(logPath, "/sdcard/KOGameBox/");
	if (NULL == opendir(logPath))
		mkdir(logPath, 0775);
#endif
	strcat(logPath, "cocos_lobby_log.txt");
	if (freopen(logPath, "a+", stdout) == NULL)
		fprintf(stderr, "重定向错误！无法输出到文本\n");


	if (setvbuf(stdout, NULL, _IONBF, 0) != 0)
		printf("failed to set up buffer for output file\n");
	else
		printf("buffer set up for output file\n");
#endif

	cb_lobby = new MatchVSDemoLobbyCallback;
	cb_pay = new MatchVSDemoPayCallback;

	CMatchVSPay::getInstance()->initWithCallback(cb_pay);
	lobby = CMatchVSLobby::getInstance();
	lobby->initWithCallback(cb_lobby);

	demoSetAuth();

	nowtoken = new char[128];
}
void  MatchVSDemoLobbyPayBundle::set_str(std::string *str)
{
	cb_lobby->hwold = str;
}

MatchVSDemoLobbyPayBundle::~MatchVSDemoLobbyPayBundle()
{
	delete cb_lobby;
	CMatchVSLobby::release();

	delete nowtoken;
}

ms_int32_t MatchVSDemoLobbyPayBundle::demoSetAuth()
{
	g_auth.i32DevelopID = 1;
	g_auth.i32GameID = 102000;
	g_auth.i32VersionGame = 1;
	g_auth.i32VersionSDK = 3;
	g_auth.pStrDeviceID = &g_pDeviceID;
	g_auth.pStrPackageName = &g_pStrPackageName;
	g_auth.pStrSignature = &g_pStrSignature;

	MatchVSInit(&g_auth);

	return MATCHVS_OK;
}

const char *  MatchVSDemoLobbyPayBundle::Handle(char const *pAct)
{
	return MatchVSDemoLobbyPayBundle::LobbyHandle(pAct, 1);
}

const char *  MatchVSDemoLobbyPayBundle::LobbyHandle(char const *pAct, int player)
{

	if (!(pAct && strkocmp(pAct, "gameLogin") && strkocmp(pAct, "All"))) {
		// if(player == 1){
		// 	KOSetUserIDToken(40, "IESCIYAKUYPRGMBTBHBZDPXNMKZGFFMN");
		// }else{
		// 	KOSetUserIDToken(41, "CDYHGSYPBHKACYBPWJVCYNCATCUVOMBB");
		// }
		
		if ( (userid = GetUserID()) && GetUserToken(nowtoken)) {
			lobby->authSet(&g_auth, userid);
			token.i32Size = 32;
			token.pData = nowtoken;
			//*(cb_lobby->hwold) = nowtoken;
			lobby->gameLogin(&token);

			//std::stringstream ss;
			//ss << userid;
			//kolock.lock();
			//*(cb_lobby->hwold) = std::string("gameLogin id: ") + ss.str() + "\n" + *(cb_lobby->hwold);
			//	*(cb_lobby->hwold) += ss.str();
			//kolock.unlock();
		}
		else
		{   DemoLock();
			*(cb_lobby->hwold) = "user no login";
			DemoUnlock();
		}
	}

	if (!(pAct && strkocmp(pAct, "roomIn") && strkocmp(pAct, "All"))) {
		lobby->roomIn();
	}

	if (!(pAct && strkocmp(pAct, "ready") && strkocmp(pAct, "All"))) {
		lobby->ready();
	}

	if (!(pAct && strkocmp(pAct, "start") && strkocmp(pAct, "All"))) {
		lobby->start();
	}
	if (!(pAct && strkocmp(pAct, "send_rand") && strkocmp(pAct, "All"))) {
		ms_str_t temprand;
		randpro temprp;
		temprp.size = sizeof(randpro);
		temprp.neti = 1;
		temprp.nums = rand();
		temprand.i32Size = sizeof(randpro);
		temprand.pData = (ms_int8_t*)&temprp;
		lobby->send(&temprand);

		std::stringstream ss;
		ss << temprp.nums;
		DemoLock();
		*(cb_lobby->hwold) = std::string("send: ") + ss.str() + "\n" + *(cb_lobby->hwold);
		//	*(cb_lobby->hwold) += ss.str();
		DemoUnlock();
		printf("formain send rand num\n");
	}
	if (!(pAct && strkocmp(pAct, "send_reliable") && strkocmp(pAct, "All"))) {
		ms_str_t temprand;
		randpro temprp;
		temprp.size = sizeof(randpro);
		temprp.neti = 1;
		temprp.nums = rand();
		temprand.i32Size = sizeof(randpro);
		temprand.pData = (ms_int8_t*)&temprp;
		lobby->sendReliable(&temprand);

		std::stringstream ss;
		ss << temprp.nums;
		DemoLock();
		//*(cb_lobby->hwold) += "\n send reliable rand num: ";
		*(cb_lobby->hwold) = std::string("sendReliable: ") + ss.str() + "\n" + *(cb_lobby->hwold);
		//*(cb_lobby->hwold) += ss.str() ;
		DemoUnlock();
		printf("formain reliable send  rand num\n");
	}

	if (!(pAct && strkocmp(pAct, "gameLogout") && strkocmp(pAct, "All"))) {
		lobby->gameLogout();
	}
	if (!(pAct && strkocmp(pAct, "roomout") && strkocmp(pAct, "All"))) {
		lobby->roomOut();
	}
	if (!(pAct && strkocmp(pAct, "gameover") && strkocmp(pAct, "All"))) {
		ms_int16_t icode = 100;
		MatchVSScore *score = new MatchVSScore;

		//typedef struct __MatchVSScore
		//{
		//	ms_int32_t                      i32UserID;
		//	ms_int32_t 						i32A;
		//	ms_int32_t 						i32B;
		//	ms_int32_t 						i32C;
		//	//2015-09-08 added by huanggaofeng
		//	ms_int32_t                      i32ExtendNum;
		//	ms_int32_t                     p32Extend[0];
		//}MatchVSScore;
		score->i32UserID = 10;
		score->i32ExtendNum = 1;
		score->i32Ext0 = 44;
		//score->p32Extend[0] = 44;

		lobby->gameOver(score);
	}

	return "";
}



ms_int32_t  MatchVSDemoLobbyCallback::onRoomInBack(ms_int32_t i32RoomID)										//加入房间结果通知
{
	DemoEcho(hwold,"onRoomInBack:%d\n", i32RoomID);
	
	SetUserStatus(UserStatus::STATUS_IN);
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoLobbyCallback::onLoginBack(MatchVSLoginRsp *pRsp)					//登录结果通知
{
	if (pRsp->i32Ret == 200)//登录成功
	{
		SetIsLoginFlag(true);
	
	}
	
	DemoEcho(hwold,"onLoginBack rsp:%d ,userid:%d\n",pRsp->i32Ret,GetUserID());
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}

/*********************************************************************************************************
	** 名称:	onUserRoomInBack
	** 描述:	回调指针类型，其他用户加入房间结果通知
	** 输入:	i32RoomID：房间ID, i32UserID：用户ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
ms_int32_t MatchVSDemoLobbyCallback::onUserRoomInBack(ms_int32_t i32RoomID, ms_int32_t i32UserID)
{
	DemoEcho(hwold,"onUserRoomInBack room:%d, user:%d\n",i32RoomID,i32UserID);
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}

/*********************************************************************************************************
	** 名称:	onGameReady
	** 描述:	回调指针类型，当前用户准备好
	** 输入:	i32RoundID：场�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
ms_int32_t  MatchVSDemoLobbyCallback::onGameReady()
{
	DemoEcho(hwold,"onReady back user:%d\n",GetUserID());
	
	
	SetUserStatus(UserStatus::STATUS_READY);
	
	if (IsOwner())
		SetStartFlag(true);
	else
		SetStartFlag(false);
	
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}
/*********************************************************************************************************
	** 名称:	onRoomInBack
	** 描述:	回调指针类型，用户退出房间结果通知
	** 输入:	�?
	** 输出�?�?
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
 ms_int32_t  MatchVSDemoLobbyCallback::onRoomOutBack()
{
	DemoEcho(hwold,"onRoomOutBack user:%d\n",GetUserID());
	ClearRoomOut();
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}

/*********************************************************************************************************
	** 名称:	onUserRoomInBack
	** 描述:	回调指针类型，其他用户退出结果通知
	** 输入:	i32UserID：用户ID
	** 输出:	�?
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
 ms_int32_t  MatchVSDemoLobbyCallback::onUserRoomOutBack(ms_int32_t i32UserID)
{
	DemoEcho(hwold,"onUserRoomOutBack userid:%d \n",i32UserID);
	SetNeedUpdateButtonFlag(true);

	return MATCHVS_OK;
};


/*********************************************************************************************************
	** 名称:	onUserGameReady
	** 描述:	回调指针类型，其他用户准备好
	** 输入:	i32RoomID：房间ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
 ms_int32_t  MatchVSDemoLobbyCallback::onUserGameReady(ms_int32_t i32UserID)
{
	DemoEcho(hwold,"onUserGameReady userid:%d \n",i32UserID);
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
};

/*********************************************************************************************************
	** 名称:	onCancelReady
	** 描述:	回调指针类型，当前用户取消游戏准�?
	** 输入:	�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
ms_int32_t  MatchVSDemoLobbyCallback::onCancelReady()
{
	DemoEcho(hwold,"onCancelReady userid:%d \n",GetUserID());
	SetUserStatus(UserStatus::STATUS_IN);
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
};

/*********************************************************************************************************
	** 名称:	onUserCancelReady
	** 描述:	回调指针类型，其他游戏用户取消游戏准�?
	** 输入:	i32UserID�?用户ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
ms_int32_t  MatchVSDemoLobbyCallback::onUserCancelReady(ms_int32_t i32UserID)
{
	DemoEcho(hwold,"onUserCancelReady userid:%d \n",i32UserID);
	return MATCHVS_OK;
};
/*********************************************************************************************************
	** 名称:	onErrBack
	** 描述:	回调指针类型，大厅错误消�?
	** 输入:	i32Ret：状态码  �?pMsg：指向ms_str_t的指针（错误信息�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
ms_int32_t  MatchVSDemoLobbyCallback::onErrBack(ms_int32_t i32Ret, ms_str_t *pMsg)
{
	DemoEcho(hwold,"errback....ErrCode:%d  msg:%s\n", i32Ret, pMsg->pData);
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoLobbyCallback::onRecv(ms_int32_t i32UserID, ms_str_t *pMsg)		//接收用户数据       //userid 0 来自所有用户（服务器中转）
{

	randpro *temprd = (randpro*)(pMsg->pData);
	DemoEcho(hwold,"onRecv�?d\n", temprd->nums);
	return MATCHVS_OK;
}

ms_int32_t  MatchVSDemoLobbyCallback::onRecvReliable(ms_int32_t i32UserID, ms_str_t *pMsg)
{
	randpro *temprd = (randpro*)(pMsg->pData);
	DemoEcho(hwold,"onRecvReliable�?d\n", temprd->nums);
	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoLobbyCallback::onGameStart(ms_int64_t i32RoundID)															//OnGameStart
{
	
	DemoEcho(hwold,"OnGameStart roundid:%lld   times:%d\n", i32RoundID, ++MatchVSDemoLobbyCallback::i);
	
	SetUserStatus(UserStatus::STATUS_START);
	
	SetNeedUpdateButtonFlag(true);

	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoLobbyCallback::onGameOver(MatchVSScore  *ppScore, ms_int32_t i32Num)				//onGameOver分数
{
	DemoEcho(hwold,"onGameOver user:%d\n",GetUserID());
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoLobbyCallback::onDelayFrame(ms_int32_t i32RoomID, MatchVSRoomDelay *pDelay, ms_int32_t i32Num)//针对帧同步开始游戏前需要的延迟上报决定的移动窗口大小的接口.;
{
	DemoEcho(hwold,"on delay frame\n");
	//KOSetNeedUpdateButton(true);
	return MATCHVS_OK;
}
ms_int32_t  MatchVSDemoLobbyCallback::onRoomDelay(ms_int32_t i32RoomID, MatchVSRoomDelay *pDelay, ms_int32_t i32Num)//房间所有人的信�?
{
	/*
	static int i = 0;
	printf("on room delay user num:%d, room id:%d\n", i32Num, i32RoomID);
	char buf[1024];
	#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
	sprintf_s(buf, sizeof(buf), "on room delay user num:%d, room id:%d\n", i32Num, i32RoomID);
	#else // defined(__linux__) || defined(__linux)
	sprintf(buf, "on room delay user num:%d, room id:%d\n", i32Num, i32RoomID);
	#endif
	KOLock();
	if (i == 2)
	{

	(*hwold) = buf;
	i = 0;
	}
	else {
	(*hwold) += buf;
	++i;
	}

	(*hwold) += '\n';
	KOUnLock();
	*/
	return MATCHVS_OK;

}


ms_int32_t  MatchVSDemoLobbyCallback::onRoomChange(MatchVSUserState *pUserState, ms_int32_t i32Num)       //当前房间动态，status: 0用户进入 status: 1  有动�?
{
	DemoEcho(hwold,"onRoomChange num:%d\n",i32Num);
	return MATCHVS_OK;
}


//ms_int32_t  myLobby::onRoomChange(MatchVSUserState *pUserState, ms_int32_t i32Num)       //当前房间动态，status: 0用户进入 status: 1  有动�?
//{
//	if (i32Num == 0) {//退出房�?
//		//KOSetRoomCurrent(0, -1);
//		KO_RoomOut_Clear();
//		return  MATCHVS_OK;
//	}
//	int i;
//	for ( i = 0; i < i32Num; i++)
//	{
//		if ((pUserState + i)->i32UserID == KOGetUserID())
//			break;
//	}
//	//-------------------------
//	int j;
//	for ( j = 0; j < i32Num; j++)//给房主使用的，非房主无效（房�?房间里仅房主一个人，房主可开始；房间有多个人，必须等到所有人都准备了才能开始。）
//	{
//		if ((pUserState + j)->i32State != 1)
//			break;
//	}
//	if (j == i32Num)
//		KORoomOwnerStart(true);
//	else
//		KORoomOwnerStart(false);
//	//-------------------------
//	pUserState = pUserState + i;
//
//	KOSetRoomCurrent(i32Num, pUserState->i32State);
//
//	const char * strstatus;
//	if (pUserState->i32State == 0) {
//		strstatus = "用户进入...";
//	}
//	else if (pUserState->i32State == 1) {
//		strstatus = "准备�?..";
//	}
//	else if (pUserState->i32State == 2) {
//		strstatus = "游戏�?..";
//	}
//
//	printf("房间有新动态： 人数:%d  \n 用户:%d  用户状�?(%d)%s\n", i32Num, pUserState->i32UserID, pUserState->i32State, strstatus);
//	char buf[1024];
//#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
//	sprintf_s(buf, sizeof(buf), "房间有新动�?人数:%d  \n 用户:%d  用户状�?(%d)%s\n", i32Num, pUserState->i32UserID, pUserState->i32State, strstatus);
//#else // defined(__linux__) || defined(__linux)
//	sprintf(buf, "房间有新动态： 人数:%d  \n 用户:%d  用户状�?(%d)%s\n", i32Num, pUserState->i32UserID, pUserState->i32State, strstatus);
//#endif
//
//	KOLock();
//	// (*hwold) += '\n';
//	// (*hwold) += buf;
//	(*hwold) = std::string(buf) + "\n" + (*hwold);
//
//	KOUnLock();
//	KOSetNeedUpdateButton(true);
//	return MATCHVS_OK;
//}
/*********************************************************************************************************
	** 名称:	onRoomOwnerChanged
	** 描述:	回调指针类型，换房间owner
	** 输入:	i32UserID：新主人的ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
ms_int32_t  MatchVSDemoLobbyCallback::onRoomOwnerChanged(ms_int32_t   i32UserID)						//换房间owner
{
	SetRoomOwner(i32UserID);
	DemoEcho(hwold,"onRoomOwnerChanged :%d\n", i32UserID);
	SetNeedUpdateButtonFlag(true);
	return MATCHVS_OK;
}




ms_int32_t MatchVSDemoPayCallback::onUseCDKey(CMatchVSPayProduct *pProducts, ms_int32_t i32Count)
{
	return MATCHVS_OK;
}

ms_int32_t MatchVSDemoPayCallback::onGetCDKey(CMatchVSPayCDKey *pCDKeys)
{
	return MATCHVS_OK;
}
ms_int32_t MatchVSDemoPayCallback::onGetMyBag(CMatchVSPayProduct *pProducts, ms_int32_t i32Count)
{
	return MATCHVS_OK;
}
ms_int32_t MatchVSDemoPayCallback::onSpend(CMatchVSPayProduct *pProducts, ms_int32_t i32Count)
{
	return MATCHVS_OK;
}
ms_int32_t MatchVSDemoPayCallback::onGetSpend(CMatchVSPayProduct *pProducts)
{
	return MATCHVS_OK;
}
ms_int32_t MatchVSDemoPayCallback::onExchange(CMatchVSPayProduct *pProducts, ms_int32_t i32Count)
{
	return MATCHVS_OK;
}
ms_int32_t MatchVSDemoPayCallback::onGetMyDiamond(ms_int32_t i32Count)
{
	return MATCHVS_OK;
}
ms_int32_t MatchVSDemoPayCallback::onCheckOrder(CMatchVSPayOrderResult *pOrderResult)
{
	return MATCHVS_OK;
}

ms_int32_t MatchVSDemoPayCallback::onPay(CMatchVSPayChargeResult *pChargeResult)
{
DemoEcho(hwold, "pay result back, count:%d, order id:%s", pChargeResult->i32Count, pChargeResult->strOrderID.pData);

	return  MATCHVS_OK;
}





