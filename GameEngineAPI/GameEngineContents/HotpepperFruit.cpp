#include "HotpepperFruit.h"
#include "ContentsEnums.h"

HotpepperFruit::HotpepperFruit() 
{
}

HotpepperFruit::~HotpepperFruit() 
{
}

void HotpepperFruit::Start()
{
	IndexNum_ = 5;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_HOTPEPPER_FRUIT);
}