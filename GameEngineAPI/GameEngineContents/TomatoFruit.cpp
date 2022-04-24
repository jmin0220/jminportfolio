#include "TomatoFruit.h"
#include "ContentsEnums.h"

TomatoFruit::TomatoFruit() 
{
}

TomatoFruit::~TomatoFruit() 
{
}

void TomatoFruit::Start()
{
	IndexNum_ = 4;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_TOMATO_FRUIT);
}