#include "HpMedicineFactory.h"

Goods* HpMedicineFactory::CreateGoods()
{
	return new Goods(
		HpMedicine,
		"Ѫ��ҩˮ",
		3
	);
}
