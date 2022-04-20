#pragma once
#include "Monster.h"

class MonsterFactory
{
public:
	virtual Monster* CreateMonster() = 0;
	virtual ~MonsterFactory();
	MonsterFactory();
};

