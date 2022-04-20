#ifndef _GOODS_H_
#define _GOODS_H_
#include <string>
#include <graphics.h>

enum GoodsId
{
	error=-1,
	Key=3,
	AttMedicine=12,
	HpMedicine,
	DefMedicine
};


class Goods
{
public:
	Goods(GoodsId id,std::string GoodsName,int max);
	Goods(){}
	GoodsId GetId();
	std::string GetGoodsName();
	int GetNum();
	void AddNum();
	void DecNum();
	void SetId(GoodsId id);
	void SetGoodsName(std::string name);
	int GetMax();
private:
	GoodsId m_Id;
	std::string m_GoodsName;
	int m_Num;
	int m_Max;
};

#endif

