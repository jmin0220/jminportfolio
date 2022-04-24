#include "GreenbeanFruit.h"
#include "ContentsEnums.h"

GreenbeanFruit::GreenbeanFruit() 
{
}

GreenbeanFruit::~GreenbeanFruit() 
{
}

void GreenbeanFruit::Start()
{
	IndexNum_ = 13;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_GREENBEAN_FRUIT);
}