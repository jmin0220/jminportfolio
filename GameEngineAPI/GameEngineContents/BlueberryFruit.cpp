#include "BlueberryFruit.h"
#include "ContentsEnums.h"

BlueberryFruit::BlueberryFruit() 
{
}

BlueberryFruit::~BlueberryFruit() 
{
}

void BlueberryFruit::Start()
{
	IndexNum_ = 17;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_BLUEBERRY_FRUIT);
}