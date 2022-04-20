#pragma once
#include "MonsterFactory.h"

class WolfMonsterFactory:public MonsterFactory
{
public:
	Monster* CreateMonster() override;
};
