#pragma once
#include <list>
#include <string>
#include <vector>

#include "Guests.h"

class Array3
{
public:
	void createArray2(int**& p, int row, int col);						//创建二维数组
	void createArray3();		//创建三维数组
	void freeArray2(int** p, int row);									//释放二维数组
	void freeArray3();
	void MapFromStr(std::string str);
	std::string MapToStr();
    int*** getGameMap()const; 
    void setGameMap(int*** mGameMap);
	std::vector<std::string> StrToList(std::string str);
	std::vector<std::string> split(const std::string& str, const std::string& pattern);
	void SetAllHeroPos(std::list<Guests> guestsList);
    int getCol() const;
    void setCol(int mCol);

    int getRow() const;
    void setRow(int mRow);

    int getHeight() const;
    void setHeight(int mHeight);

private:
	int*** m_GameMap=nullptr;
	int m_Col;
	int m_Row;
	int m_Height;


};

