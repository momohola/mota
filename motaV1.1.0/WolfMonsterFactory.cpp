#include "WolfMonsterFactory.h"

Monster* WolfMonsterFactory::CreateMonster()
{
	return new Monster(
		"狼",
		30,
		50,
		15,
		25);
}
