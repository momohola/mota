#include "DefMedicineFactory.h"

Goods* DefMedicineFactory::CreateGoods()
{
	return new Goods(
		DefMedicine,
		"����ҩˮ",
		3
	);
}
