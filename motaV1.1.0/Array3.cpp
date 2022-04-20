#include "Array3.h"
#include "DecodeJSON.h"
#include <iostream>
#include <vector>


using namespace std;
/**
 * \brief 创建二维数组
 * \param p 二维数组的指针
 * \param row 行数
 * \param col 列数
 */
void Array3::createArray2(int**& p, int row, int col)
{
	p = (int**)new int[row];
	for (int i = 0; i < row; i++)
	{
		p[i] = new int[col];
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			p[i][j] = 0;
		}
	}
}

/**
 * \brief 创建三维数组
 * \param ppp 三维数组的指针
 * \param height 高度
 * \param row 行数
 * \param col 列数
 */
void Array3::createArray3()
{
	m_GameMap = (int***)new int[m_Height];
	for (int i = 0; i < m_Height; i++)
	{
		createArray2(m_GameMap[i], m_Row, m_Col);
	}
}

/**
 * \brief 释放二维数组
 * \param p 二维数组指针
 * \param row 行数
 */
void Array3::freeArray2(int** p, int row)
{
	for (int i = 0; i < row; i++)
	{
		delete[]p[i];
	}
	delete[]p;
}


/**
 * \brief 释放三维数组
 * \param p 三维数组指针
 * \param height 高度
 * \param row 行数
 */
void Array3::freeArray3()
{
	for (int i = 0; i < m_Height; i++)
	{
		freeArray2(m_GameMap[i], m_Row);
	}
	delete[]m_GameMap;
}

/**
 * \brief 将字符串以分隔符进行分割
 * \param str 待分割的字符串
 * \param pattern 分割符
 * \return	由分割出来的字符串组成的向量
 */
std::vector<std::string> Array3::split(const std::string& str, const std::string& pattern)
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

//将地图字符串的每一个数据 都保存在向量的元素里
std::vector<std::string> Array3::StrToList(std::string str)
{
	std::vector<std::string> strList;
	bool start = false;
	int beginIndex = 0;
	int count = 0;
	for (int i = 0; i < str.length(); ++i)
	{

		if ('\"' == str.at(i) && start == false)
		{
			start = true;
			beginIndex = i + 1;
		}
		else if ('\"' == str.at(i) && start == true)
		{
			start = false;
			strList.push_back(str.substr(beginIndex, count - 1));
			count = 0;
		}
		if (start)
			count++;
	}

	return strList;
}

//由地图字符串初始化地图数组
void Array3::MapFromStr(std::string str)
{
	//解析字符串，pairMap每个元素都着保存地图的一个格子
	std::vector<std::string> pairMap=StrToList(str);

	if(m_GameMap==nullptr)
		createArray3();

	for (int height = 0; height <m_Height; ++height)
	{
		std::vector<std::string> mapVec = split(pairMap.at(height),",");

		for (int row = 0; row < m_Row; ++row)
		{
			for (int col = 0; col < m_Col; ++col)
			{
				m_GameMap[height][row][col]= std::stoi(mapVec.front());
				mapVec.erase(mapVec.begin());
			}
		}
	}
}

//将地图数组转化为地图字符串
std::string Array3::MapToStr()
{
	string result="";
	for (int height = 0; height < m_Height; ++height)
	{
		for (int row = 0; row < m_Row; ++row)
		{
			for (int col = 0; col < m_Col; ++col)
			{
				int temp = m_GameMap[height][row][col];
				if(2==temp)
				{
					result += "0";
				}
				else
				{
					result += to_string(temp);
				}
				result += ",";
			}
		}
	}
	result.erase(result.length() - 1, 1);
	return result;
}

//设置玩家和队友的位置
void Array3::SetAllHeroPos(std::list<Guests> guestsList)
{
	for (auto it = guestsList.begin(); it != guestsList.end(); it++)
	{
		if(it==guestsList.begin())
		{
			m_GameMap[0][it->getX()][it->getY()] = 2;
		}
		else
		{
			m_GameMap[0][it->getX()][it->getY()] = 15;
		}
	}
}




int*** Array3::getGameMap() const
{
    return m_GameMap;
}

void Array3::setGameMap(int*** mGameMap)
{
    m_GameMap = mGameMap;
}

int Array3::getCol() const
{
    return m_Col;
}

void Array3::setCol(int mCol)
{
    m_Col = mCol;
}

int Array3::getRow() const
{
    return m_Row;
}

void Array3::setRow(int mRow)
{
    m_Row = mRow;
}

int Array3::getHeight() const
{
    return m_Height;
}

void Array3::setHeight(int mHeight)
{
    m_Height = mHeight;
}

