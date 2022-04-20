#include "Backpack.h"
#include <iostream>

void Backpack::AddGoods(Goods* newGoods)
{
	bool flag = true;
	std::vector<Goods*>::iterator it=m_GoodsVec.begin();
	for(;it!=m_GoodsVec.end();it++)
	{
		if((*it)->GetId()== newGoods->GetId())
		{
			if((*it)->GetNum() < (*it)->GetMax())
			{
				flag = false;
				(*it)->AddNum();
				delete newGoods;
				break;
			}
			else if(it==m_GoodsVec.end()-1)
			{
				flag = true;
				break;
			}
		}
	}

	if(flag)
	{
		m_GoodsVec.push_back(newGoods);
	}

}

GoodsId Backpack::DecGoods(int index)
{
	if(index<m_GoodsVec.size()&&index>=0)
	{
		GoodsId goodsId = m_GoodsVec.at(index)->GetId();
		
		m_GoodsVec.at(index)->DecNum();
		if(m_GoodsVec.at(index)->GetNum()==0)
		{
			delete m_GoodsVec.at(index);
			m_GoodsVec.erase(m_GoodsVec.begin()+index);
		}
		
		return goodsId;
	}
	else
	{
		std::cout << "该位置没有物品" << std::endl;
		return error;
	}
}


std::vector<Goods*> Backpack::GetGoodsVec()
{
	return m_GoodsVec;
}

int Backpack::FindGoodsSum(GoodsId id)
{
	int sum = 0;
	for (auto goods : m_GoodsVec)
	{
		if(goods->GetId()==id)
		{
			sum += goods->GetNum();
		}
	}
	return sum;
}

GoodsId Backpack::FindGoods(int index)
{
	if (index> m_GoodsVec.size()-1)
		return error;
	return m_GoodsVec[index]->GetId();
}

int Backpack::FinGoodsIndex(GoodsId id)
{
	int index = 0;
	for (std::vector<Goods*>::iterator it = m_GoodsVec.begin(); it != m_GoodsVec.end(); it++)
	{
		if((*it)->GetId()==id)
		{
			return index;
		}
		index++;
	}
}

void Backpack::Clear()
{
	for (auto value : m_GoodsVec)
	{
		delete value;
	}
	m_GoodsVec.clear();
}
