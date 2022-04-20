#include "AttMedicineFactory.h"

Goods* AttMedicineFactory::CreateGoods()
{
	return new Goods(
		AttMedicine, 
		"力量药水",
		3
	);
}
