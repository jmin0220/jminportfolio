#include "YamFruit.h"
#include "ContentsEnums.h"

YamFruit::YamFruit() 
{
}

YamFruit::~YamFruit() 
{
}

void YamFruit::Start()
{
	IndexNum_ = 10;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_YAM_FRUIT);
}