#include "RhubarbFruit.h"
#include "ContentsEnums.h"

RhubarbFruit::RhubarbFruit() 
{
}

RhubarbFruit::~RhubarbFruit() 
{
}

void RhubarbFruit::Start()
{
	IndexNum_ = 3;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_RHUBARB_FRUIT);
}