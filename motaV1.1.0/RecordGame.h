#ifndef _SAVEGAME_H_
#define _SAVEGAME_H_
#include <string>

#include "DosWindows.h"
#include "GameMap.h"
class RecordGame
{
public:
	void Init(GameMap* gameMap, Hero* hero,DosWindows* dos);
	void Save();
	void Read();
private:
	std::string m_Src;
	Hero* m_Hero;
	GameMap* m_GameMap;
	ManageXML* m_XML;
	DosWindows* m_Dos;
};

#endif

