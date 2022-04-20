#pragma once
#include "MonsterFactory.h"

class BugMonsterFactory:public MonsterFactory
{
public:
	Monster* CreateMonster() override;
};

