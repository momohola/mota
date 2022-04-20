#include "BugMonsterFactory.h"

Monster* BugMonsterFactory::CreateMonster()
{
	return new Monster(
		"³æ",
		40,
		60,
		10,
		10
	);
}
