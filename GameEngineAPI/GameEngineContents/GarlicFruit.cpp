#include "GarlicFruit.h"
#include "ContentsEnums.h"

GarlicFruit::GarlicFruit() 
{
}

GarlicFruit::~GarlicFruit() 
{
}

void GarlicFruit::Start()
{
	IndexNum_ = 2;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_GARLIC_FRUIT);
}