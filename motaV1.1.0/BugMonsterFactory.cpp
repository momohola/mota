#include "BugMonsterFactory.h"

Monster* BugMonsterFactory::CreateMonster()
{
	return new Monster(
		"��",
		40,
		60,
		10,
		10
	);
}
