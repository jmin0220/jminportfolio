#include "PotatoFruit.h"
#include "ContentsEnums.h"

PotatoFruit::PotatoFruit() 
{
}

PotatoFruit::~PotatoFruit() 
{
}

void PotatoFruit::Start()
{
	IndexNum_ = 14;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_POTATO_FRUIT);
}