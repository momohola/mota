#include "Monster.h"


Monster::Monster(std::string name, int hp, int exp, int att, int def)
{
	m_Name = name;
	m_Hp = hp;
	m_Exp = exp;
	m_Att = att;
	m_Def = def;
}

int Monster::GetAtt()
{
	return m_Att;
}

int Monster::GetDef()
{
	return m_Def;
}

int Monster::GetExp()
{
	return m_Exp;
}

int Monster::GetHp()
{
	return m_Hp;
}

std::string Monster::GetName()
{
	return m_Name;
}

void Monster::SetHp(int hp)
{
	m_Hp = hp;
}
