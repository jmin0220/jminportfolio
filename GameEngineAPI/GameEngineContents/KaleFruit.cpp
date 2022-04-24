#include "KaleFruit.h"
#include "ContentsEnums.h"

KaleFruit::KaleFruit() 
{
}

KaleFruit::~KaleFruit() 
{
}

void KaleFruit::Start()
{
	IndexNum_ = 15;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_KALE_FRUIT);
}