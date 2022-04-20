#include "DosWindows.h"

#include <iostream>
#include <windows.h>

using namespace std;

DosWindows::DosWindows()
{
	m_Msg = "";
}

void DosWindows::init(GameMap* gameMap)
{
	m_GameMap = gameMap;
}


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
11公主
12 表示加攻击力药水
13 表示加血量药水
14 表示加防御力药水
15 表示传送点
*/
void DosWindows::PrintMap(Hero* hero)
{
	system("cls");
	string outStr = "";
	for (int i = 0; i < m_GameMap->GetRow(); i++) {
		for (int j = 0; j < m_GameMap->GetCol(); j++) {
			switch (m_GameMap->GetMap()[m_GameMap->GetLevel()][i][j]) {
			case 0:
				cout << "  ";
			
				break;
			case 1:
				cout << "■";
			
				break;
			case 2:
			case 10:
			case 9:
				cout << "♀";
				
				break;
			case 3:
				cout << "钥";
			
				break;
			case 4:
				cout << "门";
				break;
			case 5:
				cout << "狼";
			
				break;
			case 6:
				cout << "虫";
			
				break;
			case 7:
				cout << "上";
			
				break;
			case 8:
				cout << "下";
				
				break;
			case 11:
				cout << "公";
				
				break;
			case 12:
				cout << "功";
				
				break;
			case 13:
				cout << "血";
				
				break;
			case 14:
				cout << "防";
				
				break;
			case 15:
				cout << "友";
				
				break;
			}
		}

		PrintHeroInfo(hero,i);
		cout << endl;
		
	}
}

void DosWindows::PrintWelcome()
{
	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "                        1.开始游戏" << endl;
	cout << "                        2.结束游戏" << endl;
	cout << "                 WASD移动 P保存游戏   O加载游戏  B打开或者关闭背包，按数字键选择菜单项或者使用物品" << endl;
	cout << "                 ctrl+\\进入游戏控制台" << endl;
}

void DosWindows::ChooseMode()
{
	cout << endl << endl << endl << endl << endl << endl << endl;

	cout << "                     请选择游戏模式：" << endl;
	cout << "                        1.单机" << endl;
	cout << "                        2.联机" << endl;
}

//渲染游戏属性
void DosWindows::PrintHeroInfo(Hero* hero,int n)
{
	
	switch (n) {
	case 1:
		cout.width(8);
		cout << "\t\t英雄：" << hero->GetName();
		break;
	case 2:
		cout.width(8);
		cout << "\t\t等级：" << hero->GetLv();
		break;
	case 3:
		cout.width(8);
		cout << "\t\t血量：" << hero->GetHp();
		break;
	case 4:
		cout.width(8);
		cout << "\t\t经验：" << hero->GetExp();
		break;
	case 5:
		cout.width(8);
		cout << "\t\t攻击力：" << hero->GetAtt();
		break;
	case 6:
		cout.width(8);
		cout << "\t\t防御力：" << hero->GetDef();
		break;
	case 7:
		cout.width(8);
		cout << "\t\t提示：" << m_Msg;
		break;
	}
}

//设置提示信息
void DosWindows::SetMsg(std::string msg)
{
	m_Msg = msg;
}

//dos窗口的战斗函数
bool DosWindows::Fight(Hero* hero, Monster* monster)		
{
	PrintMap(hero);
	//回合制自动战斗
	while (true) 
	{
		//英雄攻击怪物
		if (hero->GetHp() > 0) 
		{
			int damage = hero->GetAtt() * ((float)(100 - monster->GetDef()) / 100);
			cout << hero->GetName() << "攻击了" << monster->GetName() << endl;
			cout << monster->GetName() << "失去了" << damage << "的血量" << endl;
			monster->SetHp(monster->GetHp()-damage);
			Sleep(300);
		}
		else
		{
			system("cls");
			return false;
		}

		//怪物攻击英雄
		if (monster->GetHp() > 0)
		{
			int damage = monster->GetAtt() * ((float)(100 - hero->GetDef()) / 100);
			cout << monster->GetName() << "攻击了" << hero->GetName() << endl;
			cout << hero->GetName() << "失去了" << damage << "的血量" << endl;
			hero->SetHp(hero->GetHp() - damage);
			Sleep(300);
		}
		else 
		{
			system("cls");
			return true;
		}
	}
}

void DosWindows::GameOver()
{
	cout << "游戏结束" << endl;
}

void DosWindows::GameVictory()
{
	cout << "游戏胜利" << endl;
}

//渲染背包
void DosWindows::RenderBackpack(Hero* hero)
{
	for (auto goods_vec : hero->GetBackpack()->GetGoodsVec()) 
	{
		cout << goods_vec->GetGoodsName() << "-----------数量：" << goods_vec->GetNum() << endl;
	}
}
