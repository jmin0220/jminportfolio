#include "MelonFruit.h"
#include "ContentsEnums.h"

MelonFruit::MelonFruit() 
{
}

MelonFruit::~MelonFruit() 
{
}

void MelonFruit::Start()
{
	IndexNum_ = 16;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_MELON_FRUIT);
}