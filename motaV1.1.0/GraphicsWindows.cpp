#include "GraphicsWindows.h"
# include <stdlib.h>


void GraphicsWindows::init(GameMap* gameMap)
{
	MAPWIDHT = IMGSIZE * gameMap->GetRow();
	MAPHEIGHT = IMGSIZE * gameMap->GetCol();
	m_BackpackWidth = MAPWIDHT / 2;
	WINDOWSHEIGHT = MAPHEIGHT;
	MSGWIDHT = 300;
	MSGHEIGHT = MAPWIDHT - 150;
	WINDOWSWIDHT = MAPWIDHT + MSGWIDHT;
	initgraph(WINDOWSWIDHT, WINDOWSHEIGHT, SHOWCONSOLE);
	m_GameMap = gameMap;
	LoadImg();

}


void GraphicsWindows::LoadImg()
{
	/*
0代表空地
1代表墙
2代表玩家
3表示钥匙
4表示门
5表示 怪物1
6表示 怪物2
7上楼梯（上一关）
8下楼梯（下一关）
9公主
10 表示加攻击力药水
11 表示加血量药水
12 表示加防御力药水

*/
	loadimage(&m_Img[0], _T("./img/ground.png"), IMGSIZE, IMGSIZE);		//空地
	loadimage(&m_Img[1], _T("./img/wall.bmp"), IMGSIZE, IMGSIZE);			//墙
	loadimage(&m_Img[3], _T("./img/key.bmp"), IMGSIZE, IMGSIZE);			//钥匙
	loadimage(&m_Img[4], _T("./img/Door.bmp"), IMGSIZE, IMGSIZE);			//门
	loadimage(&m_Img[5], _T("./img/monster1.bmp"), IMGSIZE, IMGSIZE);		//怪物1
	loadimage(&m_Img[6], _T("./img/monster2.bmp"), IMGSIZE, IMGSIZE);		//怪物2
	loadimage(&m_Img[7], _T("./img/upStair.bmp"), IMGSIZE, IMGSIZE);		//上楼梯
	loadimage(&m_Img[8], _T("./img/downStair.bmp"), IMGSIZE, IMGSIZE);		//下楼梯
	loadimage(&m_Img[11], _T("./img/princess.bmp"), IMGSIZE, IMGSIZE);		//公主
	loadimage(&m_Img[12], _T("./img/addAtt.bmp"), IMGSIZE, IMGSIZE);		//表示加攻击力药水
	loadimage(&m_Img[13], _T("./img/addBlood.bmp"), IMGSIZE, IMGSIZE);		//表示加血量药水
	loadimage(&m_Img[14], _T("./img/addDef.bmp"), IMGSIZE, IMGSIZE);		//表示加防御力药水

	loadimage(&m_Img[15], _T("./img/up.bmp"), IMGSIZE, IMGSIZE);   //上
	loadimage(&m_Img[16], _T("./img/down.bmp"), IMGSIZE, IMGSIZE); //下
	loadimage(&m_Img[17], _T("./img/left.bmp"), IMGSIZE, IMGSIZE); //左
	loadimage(&m_Img[18], _T("./img/right.bmp"), IMGSIZE, IMGSIZE);//右
	loadimage(&m_Img[19], _T("./img/end.png"), WINDOWSWIDHT, WINDOWSHEIGHT);//结束界面
	loadimage(&m_Img[20], _T("./img/win.png"), WINDOWSWIDHT, WINDOWSHEIGHT);//胜利界面
	loadimage(&m_Img[21], _T("./img/start.png"), WINDOWSWIDHT, WINDOWSHEIGHT);//开始界面
	loadimage(&m_Img[22], _T("./img/backpack.png"), MAPWIDHT, MAPHEIGHT);//背包
	loadimage(&m_Img[23], _T("./img/icon.png"), IMGSIZE, IMGSIZE);//金币
	loadimage(&m_Img[24], _T("./img/friend.png"), IMGSIZE, IMGSIZE);//队友
	
}


void GraphicsWindows::DisplayImg(int x, int y, int imgNum)      //在指定的下标位置显示图片
{			
	putimage(IMGSIZE * x, IMGSIZE * y, &m_Img[imgNum]);
}

void GraphicsWindows::PrintImg(int x, int y, int n,char forward)		//打印图片
{
	if (n == 2 || n == 10 || n == 9) {
		switch (forward) {
		case 'u':
			DisplayImg(x, y, 15);
			break;
		case 'd':
			DisplayImg(x, y, 16);
			break;
		case 'l':
			DisplayImg(x, y, 17);
			break;
		case 'r':
			DisplayImg(x, y, 18);
			break;
		}
	}
	else if(15==n)
	{
		DisplayImg(x, y, 24);
	}else
	{
		DisplayImg(x, y, n);
	}
}

void charToTchar(const char* _char, TCHAR* tchar) {		//char转TCHAR类型
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

//渲染背包里的物品
void GraphicsWindows::PrintGoodsWithGap(int x, int y, int n, int goodsNum)
{

	int withGapX = IMGSIZE * x+ (x-1)*m_GoodsGap;
	int withGapY = y * IMGSIZE + m_GoodsGap;
	putimage(withGapX, withGapY, &m_Img[n]);

	char value[10];
	TCHAR strValue[10];
	_itoa_s(goodsNum, value, 10);
	charToTchar(value, strValue);
	outtextxy(withGapX, withGapY, strValue);
}

//输出地图
void GraphicsWindows::PrintMap(Hero* hero)
{
	cleardevice();
	for (int i = 0; i < m_GameMap->GetRow(); i++)
	{
		for (int j = 0; j < m_GameMap->GetCol(); j++)
		{
			PrintImg(j, i, m_GameMap->GetMap()[m_GameMap->GetLevel()][i][j],hero->GetForward());
		}
	}
	PrintHeroAttribute(hero);
}

//打印欢迎图片
void GraphicsWindows::PrintWelcome()
{
	DisplayImg(0, 0, 21);
}

void GraphicsWindows::SetGameMap(GameMap* gameMap)
{
	m_GameMap = gameMap;
}

void GraphicsWindows::GameOver()
{
	DisplayImg(0, 0, 19);
}

void GraphicsWindows::GameVictory()
{
	DisplayImg(0, 0, 20);
}

//渲染背包
void GraphicsWindows::RenderBackpack(Hero* hero)
{
	cleardevice();
	DisplayImg(0, 0, 22);
	int goodsX = 1, goodsY;
	if (m_GameMap->GetRow() > 11)
		goodsY = 5;
	else
		goodsY = 3;

	for (auto goods : hero->GetBackpack()->GetGoodsVec())
	{
		goodsX++;
		PrintGoodsWithGap(goodsX, goodsY, goods->GetId(),goods->GetNum());
		if(goodsX>m_BackpackWidth)
		{
			goodsX -= m_BackpackWidth;
			goodsY++;
		}
	}
}

//渲染英雄属性
void GraphicsWindows::PrintHeroAttribute(Hero* hero)
{
	
	char value[10];
	TCHAR strHead[400] = _T("英雄：");
	TCHAR strValue[40];
	charToTchar(hero->GetName().c_str(), strValue);
	wcscat_s(strHead, strValue);
	wcscat_s(strHead, _T("\n"));

	wcscat_s(strHead, _T("等级："));
	_itoa_s(hero->GetLv(), value, 10);
	charToTchar(value, strValue);
	wcscat_s(strHead, strValue);
	wcscat_s(strHead, _T("\n"));

	wcscat_s(strHead, _T("血量："));
	_itoa_s(hero->GetHp(), value, 10);
	charToTchar(value, strValue);
	wcscat_s(strHead, strValue);
	wcscat_s(strHead, _T("\n"));

	wcscat_s(strHead, _T("经验："));
	_itoa_s(hero->GetExp(), value, 10);
	charToTchar(value, strValue);
	wcscat_s(strHead, strValue);
	wcscat_s(strHead, _T("\n"));

	wcscat_s(strHead, _T("攻击力："));
	_itoa_s(hero->GetAtt(), value, 10);
	charToTchar(value, strValue);
	wcscat_s(strHead, strValue);
	wcscat_s(strHead, _T("\n"));

	wcscat_s(strHead, _T("防御力："));
	_itoa_s(hero->GetDef(), value, 10);
	charToTchar(value, strValue);
	wcscat_s(strHead, strValue);
	wcscat_s(strHead, _T("\n"));

	RECT r = { MAPWIDHT + 5, 5, WINDOWSWIDHT, WINDOWSHEIGHT };
	drawtext(strHead, &r, DT_WORDBREAK);
}

//将字符串安装pattern进行分割
std::vector<std::string> GraphicsWindows::split(const std::string& str, const std::string& pattern)
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

void GraphicsWindows::PrintText(int x, int y, std::string text)
{
	TCHAR strValue[50];
	charToTchar(text.c_str(), strValue);
	outtextxy(x, y, strValue);
}


void GraphicsWindows::RenderHeroName(std::map<std::string, std::string> dataMap)
{
	std::string heroName = dataMap["msg"];
	heroName.erase(0, 2);
	heroName.erase(heroName.length() - 2, 2);

	std::vector<std::string> heroNameVec= split(heroName, ",");

	for (auto heroInfo : heroNameVec)
	{
		std::vector<std::string> eachItem = split(heroInfo, "_");
		int x = std::stoi(eachItem.at(3));
		int y = std::stoi(eachItem.at(2));
		std::string name = eachItem.at(1);
		PrintText(x * IMGSIZE-30, y * IMGSIZE-18, name);
	}
}

void GraphicsWindows::PrintChat(std::list<ChatMsg> charMapList)
{
	TCHAR totalChat[650]=_T("");

	for (auto value : charMapList)
	{
		TCHAR strValue[300];
		charToTchar(value.getName().c_str(), strValue);
		wcscat_s(totalChat, strValue);
		wcscat_s(totalChat, _T(":"));
		charToTchar(value.getContent().c_str(), strValue);
		wcscat_s(totalChat, strValue);
		wcscat_s(totalChat, _T("\n\n"));
	}
	SetFont();

	RECT rect = { MAPWIDHT+5, MAPHEIGHT - MSGHEIGHT,WINDOWSWIDHT, MAPHEIGHT };
	drawtext(totalChat, &rect, DT_LEFT | DT_WORDBREAK| DT_INTERNAL);
}

void GraphicsWindows::SetFont()
{
	LOGFONT font;
	gettextstyle(&font);
	font.lfHeight = 16;
	_tcscpy(font.lfFaceName, _T("等线"));
	font.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&font);
}


