#include "BeetFruit.h"
#include "ContentsEnums.h"

BeetFruit::BeetFruit() 
{
}

BeetFruit::~BeetFruit() 
{
}

void BeetFruit::Start()
{
	IndexNum_ = 11;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_BEET_FRUIT);
}