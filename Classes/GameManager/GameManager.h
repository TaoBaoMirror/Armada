#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

enum GameState
{
	GST_TITLE = 0,
	GST_LOBBY,
	GST_BATTLE,
};

class GameManager
{
public:
	~GameManager();

	static GameManager* getInstance();

	//-----------------

	void EnterBattleMap(int num);

	void EnterLobby();

protected:
	GameManager();

	static GameManager* m_Instance;

};

#endif //__GAME_MANAGER_H__