#include "EggplantFruit.h"
#include "ContentsEnums.h"

EggplantFruit::EggplantFruit() 
{
}

EggplantFruit::~EggplantFruit() 
{
}

void EggplantFruit::Start()
{
	IndexNum_ = 8;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_EGGPLANT_FRUIT);
}