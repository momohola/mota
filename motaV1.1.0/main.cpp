#include <iostream>

#include "HttpSender.h"
#include "GameController.h"
#include "Guests.h"
//HttpSender.h文件需要位于GameController.h之前

using namespace std;


int main(int argc, char* argv[])
{
	GameController* gameController=new GameController;
	gameController->GameRun();

	return 0;
}


/*
简单工厂:单一
抽象工厂:

C++项目:设计模式、动态数组、封装、继承、多态
1.英雄移动、战斗、升级
2.地图的切换(动态数组)
3.文件读写 fread fwrite
4.物品的拾取、购买、使用。
5.装备
6.任务

*/

