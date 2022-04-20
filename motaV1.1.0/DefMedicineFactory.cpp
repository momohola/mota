#include "DefMedicineFactory.h"

Goods* DefMedicineFactory::CreateGoods()
{
	return new Goods(
		DefMedicine,
		"·ÀÓùÒ©Ë®",
		3
	);
}
