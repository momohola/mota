#include "GameController.h"
#include <thread>
#include <mutex>
#include "EncodingTransform.h"
#include "ManageChat.h"

using namespace std;

std::mutex GraphicsMtx;
std::mutex DosMtx;

GameController::GameController()
{
	m_GameState = Start;
	m_Hero = new Hero("大魔王",1,100,0,11,35);
	m_GameMap = new GameMap;
	m_DosWindows = new DosWindows;
	m_GraphicsWindows = new GraphicsWindows;
	m_Host = new LocalComputerInfo;
	m_RecordGame = new RecordGame;
}

void GameController::StartGame()
{
	//在dos界面打印欢迎进入游戏
	m_DosWindows->PrintWelcome();
}


void GameController::UpdateStart()
{
	int Input = _getch();
	system("cls");
	switch (Input)
	{
	case '1':
		m_DosWindows->ChooseMode();
		Input = _getch();
		if (Input == '1')
			m_GameState =Single;//切换到单机状态
		if (Input == '2')
			m_GameState = Online;//切换到联机状态


		loadOnlineOrSigleMap(m_GameState);//选择加载单机地图还是联机地图
		break;
	case '2':
		exit(0);
		break;
	}
}

void GameController::loadOnlineOrSigleMap(GameState state)
{
	if(state==Single)//加载单机地图
	{
		//从xml文件解析地图
		m_GameMap->init("./config/GameConfig.xml");
		m_DosWindows->init(m_GameMap);
		m_GraphicsWindows->init(m_GameMap);

		//给保存游戏类初始化
		m_RecordGame->Init(m_GameMap, m_Hero,m_DosWindows);
		//确定玩家位置
		m_Hero->SetPos(m_GameMap->GetHeroPos());
	}
	if(state==Online)//加载联机地图
	{
		//访问服务器获取地图
		map<string,string> dataMap= m_GameMap->init(InitGameMap,m_Host);

		//将从服务器获取来的datamap进行解析，从key=data字段获得地图字符串，并且存入地图
		m_GameMap->MapFromDataMap(dataMap);
		//将从服务器获取来的datamap进行解析，从key=msg字段获得玩家字符串，设置玩家和队友的位置
		m_Hero->SetPos(m_GameMap->GetHeroPos(dataMap));

		//初始化dos界面和图形化界面
		m_DosWindows->init(m_GameMap);
		m_GraphicsWindows->init(m_GameMap);

		//开启多线程，渲染画面
		StartNewThread();
	}
}

void GameController::GameRun()
{
	while (true)
	{
		switch (m_GameState)
		{
		case Start:
			//打印欢迎界面
			StartGame();
			UpdateStart();
			break;
		case Single:			//单机模式
			//每次都更新画面
			m_DosWindows->PrintMap(m_Hero);
			m_GraphicsWindows->PrintMap(m_Hero);

			//英雄移动
			HeroMove(m_Hero);
			break;
		case Online:
			//在多线程中更新画面，这里只获得玩家输入，移动英雄
			HeroMove(m_Hero);

			break;
		}
	}
}


void GameController::HeroMove(Hero* hero) {
	int input = _getch();

	//按下按键后清除提示
	m_DosWindows->SetMsg("");

	int OffSetX = 0;
	int OffSetY = 0;
	switch (input) {
	case 's':
	case 'S':
		//下
		OffSetX = 1;
		hero->SetForward('d');
		break;
	case 'w':
	case 'W':
		//上
		OffSetX = -1;
		hero->SetForward('u');
		break;
	case 'd':
	case 'D':
		//右
		OffSetY = 1;
		hero->SetForward('r');
		break;
	case 'a':
	case 'A':
		//左
		OffSetY = -1;
		hero->SetForward('l');
		break;
	case 'p':
	case 'P':
		//保存游戏
		if(m_GameState==Single)
			m_RecordGame->Save();
		break;
	case 'o':
	case 'O':
		//加载游戏
		if (m_GameState == Single)
			m_RecordGame->Read();
		break;
	case 'b':
	case 'B':
		//打开背包
		
		//mtx是互斥锁，锁上是打开背包时停止渲染地图
		GraphicsMtx.lock();
		Sleep(100);

		//在dos界面渲染背包
		m_DosWindows->RenderBackpack(hero);
		//在图形化界面渲染背包
		m_GraphicsWindows->RenderBackpack(hero);

		//等待玩家使用物品 输入物品的次序使用物品
		hero->UserGoods();
		
		//解锁，继续渲染地图
		GraphicsMtx.unlock();
		break;

	case 28:
		OpenConsole();
		break;
	}

	GraphicsMtx.lock();
	//判断下一个位置的情况:
	if (0 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//空地
	{
		//修改地图数据
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX()][hero->GetPos()->GetY()] -= 2;//人离开
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] += 2;// 人进来
		//改变玩家的坐标
		hero->GetPos()->SetX(hero->GetPos()->GetX() + OffSetX);
		hero->GetPos()->SetY(hero->GetPos()->GetY() + OffSetY);
	}
	else if (3 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//钥匙
	{
		//修改地图数据
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX()][hero->GetPos()->GetY()] -= 2;//人离开
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] = 2;   //拾取钥匙
		//改变玩家的坐标和钥匙的数量
		hero->GetPos()->SetX(hero->GetPos()->GetX() + OffSetX);
		hero->GetPos()->SetY(hero->GetPos()->GetY() + OffSetY);
		//pHero->KeyNum++;
		//chargeBackpack(4, 1);
		GoodsFactory* goodsFactory = new KeyFactory;
		hero->GetBackpack()->AddGoods(goodsFactory->CreateGoods());

		delete goodsFactory;
	}
	else if (7 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//上楼梯
	{
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX()][hero->GetPos()->GetY()] -= 2;
		m_GameMap->SetLevel(m_GameMap->GetLevel()+1);
		FinHeroPosUp(hero);
	}
	else if (8 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//下楼梯
	{
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX()][hero->GetPos()->GetY()] -= 2;
		m_GameMap->SetLevel(m_GameMap->GetLevel() - 1);
		FinHeroPosDown(hero);
	}
	else if (5 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//狼
	{
		//战斗:
		MonsterFactory* monsterFactory;
		monsterFactory = new WolfMonsterFactory;
		Monster* BugMonster = monsterFactory->CreateMonster();
		if (m_DosWindows->Fight(m_Hero, BugMonster))//战斗胜利
		{
			m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] = 0;//狼死了
			//获取经验
			m_Hero->SetExp(m_Hero->GetExp()+ BugMonster->GetExp());
			//判断是否能升级
			m_Hero->LvUp();
		}
		else {
			//游戏结束
			m_DosWindows->GameOver();
			m_GraphicsWindows->GameOver();
			while (1);
		}

		delete monsterFactory;
		delete BugMonster;
	}
	else if (6 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//狼
	{
		//战斗:
		MonsterFactory* monsterFactory;
		monsterFactory = new WolfMonsterFactory;
		Monster* WolfMonster = monsterFactory->CreateMonster();
		if (m_DosWindows->Fight(m_Hero, WolfMonster))//战斗胜利
		{
			m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] = 0;//狼死了
			//获取经验
			m_Hero->SetExp(m_Hero->GetExp() + WolfMonster->GetExp());
			//判断是否能升级
			m_Hero->LvUp();
		}
		else {
			//游戏结束
			m_DosWindows->GameOver();
			m_GraphicsWindows->GameOver();
			while (1);
		}

		delete monsterFactory;
		delete WolfMonster;
	}
	else if (4 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//开门
	{
		if(hero->GetBackpack()->FindGoodsSum(Key)>0)
		{
			hero->GetBackpack()->DecGoods(hero->GetBackpack()->FinGoodsIndex(Key));
			m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] = 0;
		}
		else
		{
			m_DosWindows->SetMsg("你没有钥匙");
		}
	}
	else if (11 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//胜利
	{
		m_DosWindows->GameVictory();
		m_GraphicsWindows->GameVictory();
		while (1);
	}
	else if (12 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//攻击力药水
	{
		//物品工厂生成一个物品
		GoodsFactory* goodsFactory = new AttMedicineFactory;

		//将物品添加进背包
		hero->GetBackpack()->AddGoods(goodsFactory->CreateGoods());

		//在地图上移除物品
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] = 0;

		//销毁物品工厂
		delete goodsFactory;
	}
	else if (13 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//血量药水
	{
		GoodsFactory* goodsFactory = new HpMedicineFactory;

		hero->GetBackpack()->AddGoods(goodsFactory->CreateGoods());
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] = 0;

		delete goodsFactory;
	}
	else if (14 == m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY])//防御力药水
	{
		GoodsFactory* goodsFactory = new DefMedicineFactory;

		hero->GetBackpack()->AddGoods(goodsFactory->CreateGoods());
		m_GameMap->GetMap()[m_GameMap->GetLevel()][hero->GetPos()->GetX() + OffSetX][hero->GetPos()->GetY() + OffSetY] = 0;

		delete goodsFactory;
	}
	GraphicsMtx.unlock();
}

void GameController::FinHeroPosUp(Hero* hero)		//上楼梯
{
	for (int i = 0; i < m_GameMap->GetRow(); i++) {
		for (int j = 0; j < m_GameMap->GetCol(); j++) {
			if (8 == m_GameMap->GetMap()[m_GameMap->GetLevel()][i][j])//下楼梯的位置
			{
				//下楼梯的位置作为玩家的位置
				hero->GetPos()->SetX(i);
				hero->GetPos()->SetY(j);
				m_GameMap->GetMap()[m_GameMap->GetLevel()][i][j] = 10;//玩家和下楼梯重合
			}
		}
	}
}

void GameController::FinHeroPosDown(Hero* hero)		//下楼梯
{
	for (int i = 0; i < m_GameMap->GetRow(); i++) {
		for (int j = 0; j < m_GameMap->GetRow(); j++) {
			if (7 == m_GameMap->GetMap()[m_GameMap->GetLevel()][i][j])//下楼梯的位置
			{
				//下楼梯的位置作为玩家的位置
				hero->GetPos()->SetX(i);
				hero->GetPos()->SetY(j);
				m_GameMap->GetMap()[m_GameMap->GetLevel()][i][j] = 10;//玩家和下楼梯重合
			}
		}
	}
}

void GameController::OpenConsole()
{
	DosMtx.lock();

	system("cls");

	cout << "-------控制台-------" << endl
		<< "输入命令 \"chat\" 进入聊天频道" << endl
		<< "gethp获得血瓶，getdef获得防御药水，getatt获得攻击力药水" << endl;

	string input;
	cin >> input;
	transform(input.begin(), input.end(), input.begin(), ::tolower);
	if(input=="chat")
	{
		if(m_GameState==Single)
		{
			cout << "单机模式无法聊天" << endl;
			Sleep(2000);
			return;
		}

		cout << "输入聊天内容，按回车结束" << endl;
		while (true)
		{
			string content;
			cin >> content;

			if(content=="exit")
			{
				break;
			}

			ChatMsg chatMsg(EncodingTransform::StringToUTF8(m_Host->GetName()), EncodingTransform::StringToUTF8(content));
			ManageChat::SendChatMsg(chatMsg);

			cout << "消息已发送，退出请输入exit" << endl;
		}
	}
	else if (input == "gethp")
	{
		GoodsFactory* goodsFactory = new HpMedicineFactory;
		m_Hero->GetBackpack()->AddGoods(goodsFactory->CreateGoods());
		delete goodsFactory;
	}
	else if(input == "getdef")
	{
		GoodsFactory* goodsFactory = new DefMedicineFactory;
		m_Hero->GetBackpack()->AddGoods(goodsFactory->CreateGoods());
		delete goodsFactory;
	}
	else if (input == "getatt")
	{
		GoodsFactory* goodsFactory = new AttMedicineFactory;
		m_Hero->GetBackpack()->AddGoods(goodsFactory->CreateGoods());
		delete goodsFactory;
	}

	DosMtx.unlock();
}




//重载括号，使得GameController成为一个多线程类
void GameController::operator()()
{
	int count=0;
	map<string, string> dataMap= m_GameMap->init(InitGameMap, m_Host);
	list<ChatMsg> chatMsgList;
	while(true)
	{
		//在mtx没上锁的情况下执行下面的语句
		GraphicsMtx.lock();

		//渲染地图
		if(DosMtx.try_lock())
		{
			m_DosWindows->PrintMap(m_Hero);
			DosMtx.unlock();
		}

		m_GraphicsWindows->PrintMap(m_Hero);

		//从服务器下载聊天记录
		if (count % 10 == 0)
		{
			chatMsgList = ManageChat::GetAllChatMsg();
			count = 1;
		}
		m_GraphicsWindows->PrintChat(chatMsgList);

		m_GraphicsWindows->RenderHeroName(dataMap);
		//上传本地地图和英雄位置到服务器
		m_GameMap->Upload(m_Hero, m_Host);


		//从服务器下载地图重新初始化本地地图
		dataMap = m_GameMap->init(InitGameMap, m_Host);

		m_GameMap->MapFromDataMap(dataMap);
		m_GameMap->GetHeroPos(dataMap);

		//解锁
		GraphicsMtx.unlock();
		count++;

		Sleep(10);
	}
}

//开启多线程，异步执行GameController::operator()()函数
void GameController::StartNewThread()
{
	thread t(*this);
	t.detach();
}



GameController::~GameController()
{
	delete m_GameMap;
	delete m_Host;
	delete m_DosWindows;
	delete m_Hero;
	delete m_GraphicsWindows;
}
