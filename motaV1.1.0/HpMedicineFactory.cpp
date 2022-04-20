#include "HpMedicineFactory.h"

Goods* HpMedicineFactory::CreateGoods()
{
	return new Goods(
		HpMedicine,
		"ÑªÁ¿Ò©Ë®",
		3
	);
}
