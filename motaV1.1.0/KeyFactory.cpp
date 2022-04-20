#include "KeyFactory.h"

Goods* KeyFactory::CreateGoods()
{
	return new Goods(
		Key,
		"Ô¿³×",
		3
	);
}
