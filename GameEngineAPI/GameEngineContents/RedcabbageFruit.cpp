#include "RedcabbageFruit.h"
#include "ContentsEnums.h"

RedcabbageFruit::RedcabbageFruit()
{
}

RedcabbageFruit::~RedcabbageFruit()
{
}

void RedcabbageFruit::Start()
{
	IndexNum_ = 18;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_REDCABBAGE_FRUIT);
}