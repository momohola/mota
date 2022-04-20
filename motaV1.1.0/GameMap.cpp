#include "HttpSender.h"
#include "GameMap.h"
#include <conio.h>
#include "ManageXml.h"

using namespace std;
GameMap::GameMap()
{
	m_XML = nullptr;
	m_Map = nullptr;
	m_httpSender = nullptr;
	m_Level = 0;
}

GameMap::~GameMap()
{
	
}

//单机模式初始化游戏地图
void GameMap::init(std::string path)
{
	m_XML = ManageXML::GetInstance(path);
	m_XML->GetGameMap(m_Map);
	m_httpSender = nullptr;
	m_Level = 0;
}

//联机模式初始化游戏地图
map<string, string> GameMap::init(MsgCode msgCode,LocalComputerInfo *host)
{
	if(m_Map==nullptr)
		m_Map = new Array3;
	if(m_httpSender ==nullptr)
		m_httpSender = HttpSender::GetInstance();
	map<string, string> dataMap = m_httpSender->Receive(msgCode,host);
	//for (auto value : dataMap)
	//{
	//	cout << value.first << ":" << value.second << endl;
	//}
	return dataMap;
}

//由从服务器获得map初始化地图
void GameMap::MapFromDataMap(std::map<std::string, std::string> dataMap)
{
	if(m_Map->getCol()==0)
	{
		m_Map->setCol(stoi(dataMap.at("col")));
	}
	if (m_Map->getRow() == 0)
	{
		m_Map->setRow(stoi(dataMap.at("row")));
	}
	if (m_Map->getHeight() == 0)
	{
		m_Map->setHeight(stoi(dataMap.at("height")));
	}

	m_Map->MapFromStr(dataMap.at("mapList"));

}



int*** GameMap::GetMap()
{
	return m_Map->getGameMap();
}

int GameMap::GetCol()
{
	return m_Map->getCol();
}

int GameMap::GetRow()
{
	return m_Map->getRow();
}

int GameMap::GetLevel()
{
	return m_Level;
}

int GameMap::GetHeight()
{
	return m_Map->getHeight();
}


void GameMap::SetLevel(int level)
{
	m_Level = level;
}

HttpSender* GameMap::GetHttpSender()
{
	return m_httpSender;
}

Array3* GameMap::GetArray3()
{
	return m_Map;
}

//单机模式的得到英雄位置
Position GameMap::GetHeroPos()
{

	for (int i = 0; i < m_Map->getRow(); ++i)
	{
		for (int j = 0; j < m_Map->getCol(); ++j)
		{
			if (m_Map->getGameMap()[0][i][j] == 2)
			{
				return Position(i, j);
			}
		}
	}
	return Position();
}

//将字符串安装pattern进行分割
std::vector<std::string> GameMap::split(const std::string& str, const std::string& pattern)
{
	//const char* convert to char*
	char* strc = new char[strlen(str.c_str()) + 1];
	char* buf;

	strcpy_s(strc, strlen(str.c_str()) + 1, str.c_str());
	std::vector<std::string> resultVec;
	char* tmpStr = strtok_s(strc, pattern.c_str(), &buf);
	while (tmpStr != NULL)
	{
		resultVec.push_back(std::string(tmpStr));
		tmpStr = strtok_s(NULL, pattern.c_str(), &buf);
	}

	delete[] strc;

	return resultVec;
};

//将heroPos字符串的第一个英雄信息作为玩家英雄信息，其他为队友的信息
list<Guests> GameMap::DealHeroPos(string heroPos)
{
	heroPos.erase(0, 2);
	heroPos.erase(heroPos.length() - 2, 2);
	//cout << heroPos << endl;
	list<Guests> guestsList;

	vector<string> perGuest= split(heroPos, ",");
	for (auto value : perGuest)
	{
		vector<string> guestAttr = split(value, "_");
		Guests temp;
		temp.setId(guestAttr[0]);
		temp.setComputer(guestAttr[1]);
		temp.setX(stoi(guestAttr[2]));
		temp.setY(stoi(guestAttr[3]));

		guestsList.push_back(temp);
	}

	return guestsList;
}

//联机模式的得到英雄位置
Position GameMap::GetHeroPos(std::map<std::string, std::string> dataMap)
{
	string str = dataMap["msg"];

	//str.erase(std::remove(str.begin(), str.end(), '\\'), str.end());
	list<Guests> guestsList= DealHeroPos(str);

	m_Map->SetAllHeroPos(guestsList);
	return Position(guestsList.front().getX(),guestsList.front().getY());
}

//上传地图和英雄信息到服务器
void GameMap::Upload(Hero* hero,LocalComputerInfo *host)
{
	string mapStr = m_Map->MapToStr();
	map<string, string> temp;

	temp["gameMap"] = mapStr;
	m_httpSender->Send(UploadGameMap, temp);

	
	temp.clear();
	temp["id"] = to_string( host->GetId());
	temp["x"] = to_string(hero->GetPos()->GetX());
	temp["y"] = to_string(hero->GetPos()->GetY());

	m_httpSender->Send(UploadGameHeroPos, temp);
}



