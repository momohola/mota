#pragma once
#include "GoodsFactory.h"

class AttMedicineFactory:public GoodsFactory
{
public:
	Goods* CreateGoods() override;
};
