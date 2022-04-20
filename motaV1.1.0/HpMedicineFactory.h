#pragma once
#include "GoodsFactory.h"
class HpMedicineFactory :
    public GoodsFactory
{
    Goods* CreateGoods() override;
};

