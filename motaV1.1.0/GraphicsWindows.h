#ifndef _GRAPHICSWINDOWS_H_
#define _GRAPHICSWINDOWS_H_
#include "GameMap.h"
#include <graphics.h>

#include "ChatMsg.h"
#include "Hero.h"

//包含GameMap.h必须位于第一个

class GraphicsWindows 
{
public:

	/**
	 * \brief 加载所有图片
	 */
	void LoadImg();

	/**
	 * \brief 打印地图
	 * \param hero 玩家
	 */
	void PrintMap(Hero* hero);

	/**
	 * \brief 在（x,y）位置处显示img
	 * \param x 
	 * \param y 
	 * \param imgNum 图片下标号
	 */
	void DisplayImg(int x, int y, int imgNum);

	/**
	 * \brief 在（x,y）位置处显示img（包括英雄朝向）
	 * \param x 
	 * \param y 
	 * \param n 
	 * \param forward 
	 */
	void PrintImg(int x, int y, int n,char forward);

	/**
	 * \brief 打印欢迎界面
	 */
	void PrintWelcome();

	/**
	 * \brief 游戏结束界面
	 */
	void GameOver();

	/**
	 * \brief 游戏胜利界面
	 */
	void GameVictory();

	/**
	 * \brief 渲染玩家背包
	 * \param hero 玩家
	 */
	void RenderBackpack(Hero* hero);

	/**
	 * \brief 在（x，y）位置渲染n号物品数量为goodsNum
	 * \param x 
	 * \param y 
	 * \param n 
	 * \param goodsNum 物品数量
	 */
	void PrintGoodsWithGap(int x, int y, int n, int goodsNum);


	/**
	 * \brief 在窗口右侧打印玩家属性
	 * \param hero 玩家
	 */
	void PrintHeroAttribute(Hero* hero);

	/**
	 * \brief 渲染英雄名字
	 */
	void RenderHeroName(std::map<std::string, std::string> dataMap);

	/**
	 * \brief 初始化地图类
	 * \param gameMap 
	 */
	void init(GameMap* gameMap);


	void PrintText(int x,int y,std::string text);

	void PrintChat(std::list<ChatMsg> charMapList);

	void SetFont();
	std::vector<std::string> split(const std::string& str, const std::string& pattern);
	void SetGameMap(GameMap *gameMap);
	GraphicsWindows(){}

private:
	IMAGE m_Img[25];
	GameMap* m_GameMap;
	//每一行可以放多少个物品
	int m_BackpackWidth;
	//物品之间的间隔
	int m_GoodsGap = 10;
	int MAPWIDHT;
	int MAPHEIGHT;
	int WINDOWSWIDHT;
	int WINDOWSHEIGHT;
	int MSGWIDHT;
	int MSGHEIGHT;
	int IMGSIZE =35;

};
#endif
