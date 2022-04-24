#include "SunflowerFruit.h"
#include "ContentsEnums.h"

SunflowerFruit::SunflowerFruit() 
{
}

SunflowerFruit::~SunflowerFruit() 
{
}

void SunflowerFruit::Start()
{
	IndexNum_ = 12;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_SUNFLOWER_FRUIT);
}