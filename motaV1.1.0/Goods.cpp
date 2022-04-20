#include "Goods.h"

Goods::Goods(GoodsId id, std::string GoodsName,int max)
{
	m_Id = id;
	m_GoodsName = GoodsName;
	m_Max = max;
	m_Num = 1;
}


GoodsId Goods::GetId()
{
	return m_Id;
}

std::string Goods::GetGoodsName()
{
	return m_GoodsName;
}

void Goods::SetGoodsName(std::string name)
{
	m_GoodsName = name;
}

void Goods::SetId(GoodsId id)
{
	m_Id = id;
}

int Goods::GetNum()
{
	return m_Num;
}

void Goods::AddNum()
{
	m_Num++;
}

void Goods::DecNum()
{
	m_Num--;
}


int Goods::GetMax()
{
	return m_Max;
}

