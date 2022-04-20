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
	fopen_s(&pFile, m_Src.c_str(), "rb");   // ���ļ�  
	if (pFile == NULL)
	{
		m_Dos->SetMsg("������Ϸʧ��");
		return;
	}
	//freeArray3(GameMap, height, row);          //����ԭ��ͼ�����ᴴ���µ�ͼ
	m_GameMap->GetArray3()->freeArray3();
	int temp;
	fread(&temp, sizeof(int), 1, pFile);//		��ȡ����ĸ߶�
	m_GameMap->GetArray3()->setHeight(temp);

	fread(&temp, sizeof(int), 1, pFile);//			��ȡ���������
	m_GameMap->GetArray3()->setRow(temp);

	fread(&temp, sizeof(int), 1, pFile);//   		��ȡ���������
	m_GameMap->GetArray3()->setCol(temp);

	//createArray3(GameMap, height, row, col);				//���մ��ļ��ж�ȡ�ĸߡ��к���������һ���µ���ά����
	m_GameMap->GetArray3()->createArray3();

	cout << "heright:" << m_GameMap->GetHeight() << endl;
	cout << "row:" << m_GameMap->GetRow() << endl;
	cout << "col:" << m_GameMap->GetCol() << endl;

	for (int i = 0; i < m_GameMap->GetHeight(); i++)			//��������ȡ��ͼ
	{
		for (int j = 0; j < m_GameMap->GetRow(); j++)
		{
			fread(m_GameMap->GetMap()[i][j], sizeof(int) * m_GameMap->GetCol(), 1, pFile);
		}
	}

	fread(m_Hero, sizeof Hero, 1, pFile);			//��ȡӢ�۵�����
	Position pos;
	fread(&pos, sizeof(Position), 1, pFile);
	m_Hero->SetPos(pos);

	fread(&temp, sizeof temp, 1, pFile);			//��ȡ�ڼ���
	m_GameMap->SetLevel(temp);

	m_Hero->ReloadBackpack();
	int size;
	fread(&size, sizeof(size), 1, pFile);  //��ȡ�����Ĵ�С

	for (int i = 0; i < size; i++)							//��ȡsize����ֵ�ԣ�Ȼ����뵽map
	{
		Goods* goods=new Goods;
		fread(goods, sizeof(Goods), 1, pFile);
		m_Hero->GetBackpack()->AddGoods(goods);
	}

	m_Dos->SetMsg("������Ϸ�ɹ�");

	fclose(pFile);     // �ر��ļ�  
}

void RecordGame::Save()
{
	FILE* pFile;
	fopen_s(&pFile,m_Src.c_str(), "wb");   // ���ļ�  

	if (pFile == NULL)
	{
		m_Dos->SetMsg("������Ϸʧ��");
		return;
	}
	cout<<"heright:"<< m_GameMap->GetHeight()<<endl;
	cout<<"row:"<< m_GameMap->GetRow()<<endl;
	cout<<"col:"<< m_GameMap->GetCol()<<endl;


	int tempValue = m_GameMap->GetHeight();
	fwrite(&tempValue, sizeof(int), 1, pFile);//��
	tempValue = m_GameMap->GetRow();
	fwrite(&tempValue, sizeof(int), 1, pFile);//��
	tempValue = m_GameMap->GetCol();
	fwrite(&tempValue, sizeof(int), 1, pFile);//��

	for (int i = 0; i < m_GameMap->GetHeight(); i++)				//����ͼ����ÿһ�н���д��
	{
		for (int j = 0; j < m_GameMap->GetRow(); j++)
		{
			fwrite(m_GameMap->GetMap()[i][j], sizeof(int) * m_GameMap->GetCol(), 1, pFile);
		}
	}

	fwrite(m_Hero, sizeof Hero, 1, pFile);		//д��Ӣ��
	fwrite(m_Hero->GetPos(), sizeof Position, 1, pFile);
	tempValue = m_GameMap->GetLevel();
	fwrite(&tempValue, sizeof tempValue, 1, pFile);	//д��ؿ���


	int size = m_Hero->GetBackpack()->GetGoodsVec().size();
	fwrite(&size, sizeof(size), 1, pFile);   //�洢�����Ĵ�С

	for (auto it : m_Hero->GetBackpack()->GetGoodsVec())						//����map��key  ��value�ֱ�洢
	{
		fwrite(it, sizeof(*it), 1, pFile);
	}

	m_Dos->SetMsg("������Ϸ�ɹ�");

	fclose(pFile);     // �ر��ļ�  
}

