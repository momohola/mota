#include "RecordGame.h"

using namespace std;

void RecordGame::Init(GameMap* gameMap, Hero* hero,DosWindows* dos)
{
	m_Hero = hero;
	m_GameMap = gameMap;
	m_Dos = dos;
	m_XML = ManageXML::GetInstance();
	m_Src = m_XML->GetSaveFilePath();
}


void RecordGame::Read()
{
	FILE* pFile;
	fopen_s(&pFile, m_Src.c_str(), "rb");   // 打开文件  
	if (pFile == NULL)
	{
		m_Dos->SetMsg("加载游戏失败");
		return;
	}
	//freeArray3(GameMap, height, row);          //销毁原地图，待会创建新地图
	m_GameMap->GetArray3()->freeArray3();
	int temp;
	fread(&temp, sizeof(int), 1, pFile);//		读取数组的高度
	m_GameMap->GetArray3()->setHeight(temp);

	fread(&temp, sizeof(int), 1, pFile);//			读取数组的行数
	m_GameMap->GetArray3()->setRow(temp);

	fread(&temp, sizeof(int), 1, pFile);//   		读取数组的列数
	m_GameMap->GetArray3()->setCol(temp);

	//createArray3(GameMap, height, row, col);				//按照从文件中读取的高、行和列来创建一个新的三维数组
	m_GameMap->GetArray3()->createArray3();

	cout << "heright:" << m_GameMap->GetHeight() << endl;
	cout << "row:" << m_GameMap->GetRow() << endl;
	cout << "col:" << m_GameMap->GetCol() << endl;

	for (int i = 0; i < m_GameMap->GetHeight(); i++)			//按行来读取地图
	{
		for (int j = 0; j < m_GameMap->GetRow(); j++)
		{
			fread(m_GameMap->GetMap()[i][j], sizeof(int) * m_GameMap->GetCol(), 1, pFile);
		}
	}

	fread(m_Hero, sizeof Hero, 1, pFile);			//读取英雄的数据
	Position pos;
	fread(&pos, sizeof(Position), 1, pFile);
	m_Hero->SetPos(pos);

	fread(&temp, sizeof temp, 1, pFile);			//读取第几关
	m_GameMap->SetLevel(temp);

	m_Hero->ReloadBackpack();
	int size;
	fread(&size, sizeof(size), 1, pFile);  //读取背包的大小

	for (int i = 0; i < size; i++)							//读取size个键值对，然后加入到map
	{
		Goods* goods=new Goods;
		fread(goods, sizeof(Goods), 1, pFile);
		m_Hero->GetBackpack()->AddGoods(goods);
	}

	m_Dos->SetMsg("加载游戏成功");

	fclose(pFile);     // 关闭文件  
}

void RecordGame::Save()
{
	FILE* pFile;
	fopen_s(&pFile,m_Src.c_str(), "wb");   // 打开文件  

	if (pFile == NULL)
	{
		m_Dos->SetMsg("保存游戏失败");
		return;
	}
	cout<<"heright:"<< m_GameMap->GetHeight()<<endl;
	cout<<"row:"<< m_GameMap->GetRow()<<endl;
	cout<<"col:"<< m_GameMap->GetCol()<<endl;


	int tempValue = m_GameMap->GetHeight();
	fwrite(&tempValue, sizeof(int), 1, pFile);//列
	tempValue = m_GameMap->GetRow();
	fwrite(&tempValue, sizeof(int), 1, pFile);//行
	tempValue = m_GameMap->GetCol();
	fwrite(&tempValue, sizeof(int), 1, pFile);//列

	for (int i = 0; i < m_GameMap->GetHeight(); i++)				//将地图按照每一行进行写入
	{
		for (int j = 0; j < m_GameMap->GetRow(); j++)
		{
			fwrite(m_GameMap->GetMap()[i][j], sizeof(int) * m_GameMap->GetCol(), 1, pFile);
		}
	}

	fwrite(m_Hero, sizeof Hero, 1, pFile);		//写入英雄
	fwrite(m_Hero->GetPos(), sizeof Position, 1, pFile);
	tempValue = m_GameMap->GetLevel();
	fwrite(&tempValue, sizeof tempValue, 1, pFile);	//写入关卡数


	int size = m_Hero->GetBackpack()->GetGoodsVec().size();
	fwrite(&size, sizeof(size), 1, pFile);   //存储背包的大小

	for (auto it : m_Hero->GetBackpack()->GetGoodsVec())						//遍历map将key  和value分别存储
	{
		fwrite(it, sizeof(*it), 1, pFile);
	}

	m_Dos->SetMsg("保存游戏成功");

	fclose(pFile);     // 关闭文件  
}

