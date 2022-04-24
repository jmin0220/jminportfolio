#include "CouliflowerFruit.h"
#include "ContentsEnums.h"

CouliflowerFruit::CouliflowerFruit() 
{
}

CouliflowerFruit::~CouliflowerFruit() 
{
}

void CouliflowerFruit::Start()
{
	IndexNum_ = 1;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_COULIFLOWER_FRUIT);
}