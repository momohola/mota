#ifndef _MONSTER_H_
#define _MONSTER_H_
#include <string>

class Monster
{
public:
	Monster(std::string name, int hp, int exp, int att, int def);
	std::string GetName();
	int GetHp();
	int GetExp();
	int GetAtt();
	int GetDef();
	void SetHp(int hp);
private:
	std::string m_Name;
	int m_Hp;//血量
	int m_Exp;//经验
	int m_Att;//攻击力
	int m_Def;//防御力
};

#endif
