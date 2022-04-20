#pragma once
#include "HttpSender.h"
#include "Hero.h"
#include "Position.h"
#include "ManageXml.h"
#include "IdentityKind.h"
#include "Guests.h"
//包含HttpSender.h必须位于第一个


class GameMap
{
public:
	GameMap();
	~GameMap();
	void init(std::string path);
	std::map<std::string, std::string> init(MsgCode msgCode,LocalComputerInfo *host);
	Position GetHeroPos();
	Position GetHeroPos(std::map<std::string, std::string> dataMap);
	std::vector<std::string> split(const std::string& str, const std::string& pattern);
	std::list<Guests> DealHeroPos(std::string heroPos);
	void MapFromDataMap(std::map<std::string, std::string>);
	void Upload(Hero* hero,LocalComputerInfo* host);


	int*** GetMap();
	int GetCol();
	int GetRow();
	int GetLevel();
	int GetHeight();
	HttpSender* GetHttpSender();
	void SetLevel(int level);
	Array3* GetArray3();
private:
	int m_Level;
	ManageXML* m_XML;
	HttpSender* m_httpSender;
	Array3* m_Map;
};

