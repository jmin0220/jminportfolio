#include "RadishFruit.h"
#include "ContentsEnums.h"

RadishFruit::RadishFruit() 
{
}

RadishFruit::~RadishFruit() 
{
}

void RadishFruit::Start()
{
	IndexNum_ = 6;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_RADISH_FRUIT);
}