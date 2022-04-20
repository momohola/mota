#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_
#include "DosWindows.h"
#include "GraphicsWindows.h"
#include <cstdlib>
#include <conio.h>
#include <iostream>
#include "Hero.h"
#include "Goods.h"
#include "MonsterFactory.h"
#include "WolfMonsterFactory.h"
#include "BugMonsterFactory.h"
#include "GoodsFactory.h"
#include "AttMedicineFactory.h"
#include "DefMedicineFactory.h"
#include "HpMedicineFactory.h"
#include "KeyFactory.h"
#include "RecordGame.h"
#include "ManageChat.h"
/*
 * 包含DosWindows.h和GraphicsWindows.h必须位于第一个
 */

enum GameState {
	Start,
	Single,
	Win,
	Online
};

class GameController
{
public:
	GameController();
	~GameController();
	void GameRun();
	void HeroMove(Hero* hero);
	void FinHeroPosUp(Hero* hero);
	void FinHeroPosDown(Hero* hero);
	void operator()();
	void StartNewThread();
	void OpenConsole();
private:
	void StartGame();
	void UpdateStart();
	void loadOnlineOrSigleMap(GameState state);
private:
	GameState m_GameState;
	Hero* m_Hero;
	DosWindows *m_DosWindows;
	GraphicsWindows* m_GraphicsWindows;
	GameMap* m_GameMap;
	LocalComputerInfo* m_Host;
	RecordGame* m_RecordGame;
	
};

#endif
