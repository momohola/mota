#ifndef _HERO_H_
#define _HERO_H_
#include <string>

#include "Backpack.h"
#include "Position.h"


class Hero
{
public:
	Hero(std::string name, int lv, int hp, int exp, int att, int def);
	std::string GetName();
	Position* GetPos();
	int GetLv();
	int GetHp();
	int GetExp();
	int GetAtt();
	int GetDef();
	char GetForward();
	void SetForward(char forward);
	Backpack* GetBackpack();
	void SetPos(Position pos);
	void SetHp(int hp);
	void SetExp(int exp);

	/**
	 * \brief 英雄升级
	 */
	void LvUp();

	/**
	 * \brief 英雄使用物品，输入物品的次序可以使用物品
	 */
	void UserGoods();

	void ReloadBackpack();

private:
	std::string m_Name;//名字
	Position *m_Pos;
	int m_Lv;//等级
	int m_Hp;//血量
	int m_Exp;//经验
	int m_Att;//攻击力
	int m_Def;//防御力
	Backpack *m_Backpack;
	char m_Forward;
};


#endif
