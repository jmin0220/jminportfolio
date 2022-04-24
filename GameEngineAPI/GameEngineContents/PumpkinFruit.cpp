#include "PumpkinFruit.h"
#include "ContentsEnums.h"

PumpkinFruit::PumpkinFruit() 
{
}

PumpkinFruit::~PumpkinFruit() 
{
}

void PumpkinFruit::Start()
{
	IndexNum_ = 9;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_PUMPKIN_FRUIT);
}