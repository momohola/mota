#pragma once
#include "GoodsFactory.h"
class KeyFactory :
    public GoodsFactory
{
    virtual Goods* CreateGoods()override;
};

