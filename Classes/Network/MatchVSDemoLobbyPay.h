#ifndef __FORMAIN__
#define __FORMAIN__

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#include <winsock2.h>
#include <windows.h>

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
#include <stdlib.h>
#include "MatchVSBase.h"
#include "MatchVSLobby.h"
#include "MatchVSPay.h"
#include "cocos2d.h"
#include "CommonMutex.h"
#include "MatchVSDemoCommon.h"

USING_NS_CC;




typedef struct randpro {
	ms_int32_t size;
	ms_int32_t neti;
	ms_int32_t nums;
}randpro;

class  MatchVSDemoLobbyCallback : public CMatchVSLobbyCallback {
public:
	MatchVSDemoLobbyCallback() {}
	~MatchVSDemoLobbyCallback() {}
	std::string *hwold;
	static int i;


	/*********************************************************************************************************
	** 名称:	onRoomInBack
	** 描述:	回调指针类型，当前用户加入房间结果通知
	** 输入:	i32RoomID：房间ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onRoomInBack(ms_int32_t i32RoomID);

	/*********************************************************************************************************
	** 名称:	onUserRoomInBack
	** 描述:	回调指针类型，其他用户加入房间结果通知
	** 输入:	i32RoomID：房间ID, i32UserID：用户ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onUserRoomInBack(ms_int32_t i32RoomID, ms_int32_t i32UserID);

	/*********************************************************************************************************
	** 名称:	onLoginBack
	** 描述:	回调指针类型，登录结果通知
	** 输入:	pRsp：指向MatchVSLoginRsp的指针�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onLoginBack(MatchVSLoginRsp *pRsp);

	/*********************************************************************************************************
	** 名称:	onRoomInBack
	** 描述:	回调指针类型，用户退出房间结果通知
	** 输入:	�?
	** 输出�?�?
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onRoomOutBack();

	/*********************************************************************************************************
	** 名称:	onUserRoomInBack
	** 描述:	回调指针类型，其他用户退出结果通知
	** 输入:	i32UserID：用户ID
	** 输出:	�?
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onUserRoomOutBack(ms_int32_t i32UserID);

	/*********************************************************************************************************
	** 名称:	onErrBack
	** 描述:	回调指针类型，大厅错误消�?
	** 输入:	i32Ret：状态码  �?pMsg：指向ms_str_t的指针（错误信息�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onErrBack(ms_int32_t i32Ret, ms_str_t *pMsg);

	/*********************************************************************************************************
	** 名称:	onRecv
	** 描述:	回调指针类型�?/接收用户数据�?userid 0 来自所有用户（服务器中转）
	** 输入:	i32UserID：用户ID�? pMsg：指向ms_str_t的指针（返回的数据）
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onRecv(ms_int32_t i32UserID, ms_str_t *pMsg);

	/*********************************************************************************************************
	** 名称:	onRecvReliable
	** 描述:	可靠消息回调指针类型�?/接收用户数据�?userid 0 来自所有用户（服务器中转）
	** 输入:	i32UserID：用户ID�? pMsg：指向ms_str_t的指针（返回的数据）
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onRecvReliable(ms_int32_t i32UserID, ms_str_t *pMsg);

	/*********************************************************************************************************
	** 名称:	onGameReady
	** 描述:	回调指针类型，当前用户准备好
	** 输入:	i32RoundID：场�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onGameReady();

	/*********************************************************************************************************
	** 名称:	onUserGameReady
	** 描述:	回调指针类型，其他用户准备好
	** 输入:	i32RoomID：房间ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onUserGameReady(ms_int32_t i32UserID);

	/*********************************************************************************************************
	** 名称:	onCancelReady
	** 描述:	回调指针类型，当前用户取消游戏准�?
	** 输入:	�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onCancelReady();

	/*********************************************************************************************************
	** 名称:	onUserCancelReady
	** 描述:	回调指针类型，其他游戏用户取消游戏准�?
	** 输入:	i32UserID�?用户ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onUserCancelReady(ms_int32_t i32UserID);

	/*********************************************************************************************************
	** 名称:	onGameStart
	** 描述:	回调指针类型�?/当前用户游戏开�?
	** 输入:	i32RoundID：场次ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onGameStart(ms_int64_t i32RoundID);

	/*********************************************************************************************************
	** 名称:	onGameOver
	** 描述:	回调指针类型�?/游戏结束分数下发
	** 输入:	pScore：指向MatchVSScore的指针， i32Num：分�?
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onGameOver(MatchVSScore  *ppScore, ms_int32_t i32Num);

	/*********************************************************************************************************
	** 名称:	onRoomOwnerChanged
	** 描述:	回调指针类型，换房间owner
	** 输入:	i32UserID：新主人的ID
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onRoomOwnerChanged(ms_int32_t   i32UserID);

	/*********************************************************************************************************
	** 名称:	onDelayFrame
	** 描述:	回调指针类型�?/针对帧同步开始游戏前需要的延迟上报决定的移动窗口大小的接口.;
	** 输入:	i32RoomID：房间ID�?pDelay：指向MatchVSRoomDelay的指�?�?i32Num：延时帧个数
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onDelayFrame(ms_int32_t i32RoomID, MatchVSRoomDelay *pDelay, ms_int32_t i32Num);

	/*********************************************************************************************************
	** 名称:	onRoomDelay
	** 描述:	回调指针类型�?/房间所有人的信�?
	** 输入:	i32RoomID：房间ID�?pDelay：指向MatchVSRoomDelay的指�? �?i32Num：状态码
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onRoomDelay(ms_int32_t i32RoomID, MatchVSRoomDelay *pDelay, ms_int32_t i32Num);

	/*********************************************************************************************************
	** 名称:	onRoomChange
	** 描述:	回调指针类型�?//当前房间动态，status: 0用户进入 status: 1用户准备�?2用户开�?
	** 输入:	pUserState：指向MatchVSUserState结构体，i32Num：状态码
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onRoomChange(MatchVSUserState *pUserState, ms_int32_t i32Num);


	/*********************************************************************************************************
	** 名称:	onMessage
	** 描述:	收到消息回调
	** 输入:	pMsg�?消息
	** 输出:
	** 返回:	正确�?MATCHVS_OK  错误 �?其他�?
	*********************************************************************************************************/
	virtual ms_int32_t onMessage(ms_str_t* pMsg) { return MATCHVS_OK; };


};


class MatchVSDemoPayCallback : public CMatchVSPayCallback
{
public:
	MatchVSDemoPayCallback() {}
	~MatchVSDemoPayCallback() {}
	std::string *hwold;

	ms_int32_t onUseCDKey(CMatchVSPayProduct *pProducts, ms_int32_t i32Count);
	ms_int32_t onGetCDKey(CMatchVSPayCDKey *pCDKeys);
	ms_int32_t onGetMyBag(CMatchVSPayProduct *pProducts, ms_int32_t i32Count);
	ms_int32_t onSpend(CMatchVSPayProduct *pProducts, ms_int32_t i32Count);
	ms_int32_t onGetSpend(CMatchVSPayProduct *pProducts);
	ms_int32_t onExchange(CMatchVSPayProduct *pProducts, ms_int32_t i32Count);
	ms_int32_t onGetMyDiamond(ms_int32_t i32Count);
	ms_int32_t onCheckOrder(CMatchVSPayOrderResult *pOrderResult);
	ms_int32_t onPay(CMatchVSPayChargeResult *pChargeResult);
};


class MatchVSDemoLobbyPayBundle
{
public:

	~MatchVSDemoLobbyPayBundle();
	static MatchVSDemoLobbyPayBundle * getInstance();
	static void release();
	ms_int32_t demoSetAuth();
	const char * Handle(char const *pAct);
	const char * LobbyHandle(char const *pAct, int player);
	void set_str(std::string *str);
	ms_int32_t strkocmp(const char * str1, const char *str2);

	MatchVSAuth g_auth;
	MatchVSDemoLobbyCallback *cb_lobby;
	MatchVSDemoPayCallback *cb_pay;
	CMatchVSLobby *lobby;
	ms_str_t   token;
	std::string m_str;
	ms_int32_t userid;
	ms_int8_t *nowtoken;



private:
	MatchVSDemoLobbyPayBundle();
	static MatchVSDemoLobbyPayBundle * single;

};


#endif