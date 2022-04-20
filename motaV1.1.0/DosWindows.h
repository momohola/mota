#ifndef _DOSWINDOWS_H_
#define _DOSWINDOWS_H_
#include "GameMap.h"
#include "Hero.h"
#include "Monster.h"

//包含GameMap.h必须位于第一个

class DosWindows
{
public:
	void PrintMap(Hero* hero);
	void PrintWelcome();
	void ChooseMode();
	void PrintHeroInfo(Hero* hero,int n);
	void SetMsg(std::string msg);
	bool Fight(Hero* pHero, Monster* pMonster);
	void GameOver();
	void GameVictory();
	void RenderBackpack(Hero* hero);
	void init(GameMap* gameMap);
	DosWindows();
private:
	std::string m_Msg;
	GameMap* m_GameMap;
};


#endif


