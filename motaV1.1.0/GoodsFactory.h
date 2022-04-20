#pragma once
#include "Goods.h"

class GoodsFactory
{
public:
	virtual Goods* CreateGoods() = 0;
	virtual ~GoodsFactory();
};

