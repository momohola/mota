#pragma once
#include "GoodsFactory.h"
class DefMedicineFactory :
    public GoodsFactory
{
    Goods* CreateGoods() override;
};

