#include "KeyFactory.h"

Goods* KeyFactory::CreateGoods()
{
	return new Goods(
		Key,
		"Կ��",
		3
	);
}
