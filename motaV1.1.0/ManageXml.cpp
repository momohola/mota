#include "ManageXml.h"
#include <iostream>
#include <vector>


using namespace std;
using namespace tinyxml2;

ManageXML::ManageXML()
{
	m_Map = new Array3;
}

ManageXML::ManageXML(std::string path)
{
	m_Map = new Array3;
	deCodeXml(path);
}


/**
 * \brief 将除了字母、数字以外的字符全部删除
 * \param str 需要删除特殊符号的字符串
 */
void ManageXML::trim(string& str) {
	if (str.empty()) 
	{
		return;
	}
	str.erase(std::remove_if(str.begin(), str.end(), &ispunct), str.end());
	str.erase(std::remove_if(str.begin(), str.end(), &isspace), str.end());
}

/**
 * \brief 将除了字母、数字、标点符号以外的字符全部删除
 * \param str 需要删除特殊符号的字符串
 */
void ManageXML::trimWithoutPunct(string& str) {
	if (str.empty()) {
		return;
	}
	str.erase(std::remove_if(str.begin(), str.end(), &isspace), str.end());
}


/**
 *\brief 对XMl文件进行解码
 *\param XMLFile XML文件的保存路径
 */
void ManageXML::deCodeXml(std::string XMLFile)
{
	XMLDocument xml;

	//导入xml文件
	if (xml.LoadFile(XMLFile.c_str()) != XML_SUCCESS)
	{
		cout << "没找到文件" << endl;
		return;
	}

	//找到导入的xml的根节点
	XMLElement* rootNode = xml.RootElement();
	if (rootNode == NULL) 
	{
		return;
	}


	XMLElement* nameNode = rootNode->FirstChildElement("name");
	m_GameName = nameNode->GetText();
	trim(m_GameName);

	XMLElement* versionNode = rootNode->FirstChildElement("version");
	m_Version = versionNode->GetText();
	trimWithoutPunct(m_Version);

	XMLElement* saveFilePathNode = rootNode->FirstChildElement("saveFilePath");
	XMLElement* mapNode = saveFilePathNode->FirstChildElement("save");
	m_SaveFilePath = mapNode->GetText();
	trimWithoutPunct(m_SaveFilePath);

	//解码游戏地图
	InitGameMap(xml);

	xml.Clear();
}


/**
 * \brief 将字符串以分隔符进行分割
 * \param str 待分割的字符串
 * \param pattern 分割符
 * \return	由分割出来的字符串组成的向量 
 */
vector<std::string> split(const std::string& str, const std::string& pattern) {
	//const char* convert to char*
	char* strc = new char[strlen(str.c_str()) + 1];
	char* buf;

	strcpy_s(strc, strlen(str.c_str()) + 1, str.c_str());
	std::vector<std::string> resultVec;
	char* tmpStr = strtok_s(strc, pattern.c_str(),&buf);
	while (tmpStr != NULL) {
		resultVec.push_back(std::string(tmpStr));
		tmpStr = strtok_s(NULL, pattern.c_str(), &buf);
	}

	delete[] strc;

	return resultVec;
};


/**
 * \brief 从配置文件中读取地图
 * \param xml 配置文件
 */
void ManageXML::InitGameMap(const XMLDocument &xml)
{
	const XMLElement* rootNode = xml.RootElement();
	const XMLElement* gameMapNode = rootNode->FirstChildElement("gameMap");
	const XMLElement* rowNode = gameMapNode->FirstChildElement("row");
	const XMLElement* colNode = gameMapNode->FirstChildElement("col");
	const XMLElement* heightNode = gameMapNode->FirstChildElement("height");

	m_Map->setRow(atoi(rowNode->GetText()));
	m_Map->setCol(atoi(colNode->GetText()));
	m_Map->setHeight(atoi(heightNode->GetText()));

	m_Map-> createArray3();

	for (int height = 0; height < m_Map->getHeight(); ++height)
	{
		string label = "level"+to_string(height+1);
		const XMLElement* levelNode = gameMapNode->FirstChildElement(label.c_str());
	
		vector<std::string> mapVec =split(levelNode->GetText(), ",");


		for (int row = 0; row < m_Map->getRow(); ++row)
		{
			for (int col = 0; col < m_Map->getCol(); ++col)
			{
				m_Map->getGameMap()[height][row][col]= atoi(mapVec.front().c_str());
				mapVec.erase(mapVec.begin());
				
			}
		}
	}
}


ManageXML* ManageXML::GetInstance(std::string src)
{
	static ManageXML instance(src);
	return &instance;
}



/**
 * \brief 获得游戏名称
 * \return 
 */
std::string ManageXML::GetGameName()
{
	return m_GameName;
}


/**
 * \brief 获得游戏版本
 * \return 
 */
std::string ManageXML::GetVersion()
{
	return m_Version;
}


/**
 * \brief 获得保存文件的路径
 * \return 
 */
std::string ManageXML::GetSaveFilePath()
{
	return m_SaveFilePath;
}


/**
 * \brief 获得游戏地图
 * \param ppp 游戏地图的三级指针
 * \param height 游戏地图的层级
 * \param row 地图行数
 * \param col 地图列数
 */
void ManageXML::GetGameMap(Array3* (&map))
{
	map = m_Map;
}

























