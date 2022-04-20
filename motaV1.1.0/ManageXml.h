#pragma once
#include "tinyxml2.h"
#include <string>
#include "Array3.h"

class ManageXML
{
public:
	

	void deCodeXml(std::string XMLFile);
	void trim(std::string& str);
	void trimWithoutPunct(std::string& str);
	std::string GetGameName();
	std::string GetVersion();
	std::string GetSaveFilePath();
	void GetGameMap(Array3* (&map));
	static ManageXML* GetInstance(std::string src="./config/GameConfig.xml");
private:
	ManageXML();
	~ManageXML(){}
	ManageXML(const ManageXML&);
	ManageXML& operator=(const ManageXML&);
	ManageXML(std::string path);
	void InitGameMap(const tinyxml2::XMLDocument& xml);

private:
	std::string m_GameName;
	std::string m_Version;
	std::string m_SaveFilePath;
	Array3* m_Map;
};
