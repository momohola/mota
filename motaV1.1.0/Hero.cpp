#include "Hero.h"

#include <conio.h>
#include <iostream>
#include <ostream>

Hero::Hero(std::string name, int lv, int hp, int exp, int att, int def)
{
	m_Name = name;
	m_Pos = new Position();
	m_Lv = lv;
	m_Hp = hp;
	m_Exp = exp;
	m_Att = att;
	m_Def = def;
	m_Backpack = new Backpack();
	m_Forward = 'w';
}



int Hero::GetHp()
{
	return m_Hp;
}

int Hero::GetAtt()
{
	return m_Att;
}

int Hero::GetDef()
{
	return m_Def;
}

int Hero::GetExp()
{
	return m_Exp;
}

int Hero::GetLv()
{
	return m_Lv;
}

std::string Hero::GetName()
{
	return m_Name;
}

Position* Hero::GetPos()
{
	return m_Pos;
}

Backpack* Hero::GetBackpack()
{
	return m_Backpack;
}

char Hero::GetForward()
{
	return m_Forward;
}

void Hero::SetPos(Position pos)
{
	m_Pos->SetX(pos.GetX());
	m_Pos->SetY(pos.GetY());
}

void Hero::SetForward(char forward)
{
	m_Forward = forward;
}

void Hero::SetHp(int hp)
{
	m_Hp = hp;
}

void Hero::SetExp(int exp)
{
	m_Exp = exp;
}



void Hero::LvUp()			//英雄升级函数
{
	//升级所需经验=等级*100;
	while (m_Exp > m_Lv * 100) 
	{
		m_Exp -= m_Lv * 100;
		m_Lv++;
		//修改其他属性
		m_Hp = m_Hp + 20;
		m_Att = m_Att + 3;
		m_Def = m_Def + 3;
	}
}

void Hero::UserGoods()
{
	int input = _getch();

	if (input!='b' && input!='B')
	{
		input -= '0' + 1;
		GoodsId id = m_Backpack->FindGoods(input);
		std::cout << "id:" << id << std::endl;
		if (id == AttMedicine || id == DefMedicine || id == HpMedicine)
		{
			GoodsId result = m_Backpack->DecGoods(input);
			if (result != -1)
			{
				switch (result)
				{
				case error:
					break;
				case Key:
					break;
				case AttMedicine:
					m_Att += 3;
					break;
				case HpMedicine:
					m_Hp += 20;
					break;
				case DefMedicine:
					m_Def += 5;
					break;
				default:;
				}
			}
		}
	}
}

void Hero::ReloadBackpack()
{
	m_Backpack->Clear();
	delete m_Backpack;
	m_Backpack = new Backpack;
}




