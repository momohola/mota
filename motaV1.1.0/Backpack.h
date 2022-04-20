#ifndef _BACKPACK_H_
#define _BACKPACK_H_
#include <vector>
#include "Goods.h"


class Backpack
{
public:
	/**
	 * \brief 将物品添加进背包
	 * \param newGoods 需要添加进背包的物品指针
	 */
	void AddGoods(Goods* newGoods);


	/**
	 * \brief 删除指定下标对应的物品
	 * \param index 待删除物品的下标
	 * \return 删除的物品
	 */
	GoodsId DecGoods(int index);

	/**
	 * \brief 查找指定物品id的数量
	 * \param id 待查找物品的id
	 * \return 查找到的物品的数量
	 */
	int FindGoodsSum(GoodsId id);

	/**
	 * \brief 返回指定位置的物品
	 * \param index 指定的位置
	 * \return 物品		
	 */
	GoodsId FindGoods(int index);

	/**
	 * \brief 查找指定物品id的下标值
	 * \param id 待查找物品的id
	 * \return 查找到的物品的下标
	 */
	int FinGoodsIndex(GoodsId id);

	void Clear();

	std::vector<Goods*> GetGoodsVec();
private:	
	std::vector<Goods*> m_GoodsVec;
};

#endif
