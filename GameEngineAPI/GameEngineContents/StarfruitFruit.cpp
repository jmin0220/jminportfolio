#include "StarfruitFruit.h"
#include "ContentsEnums.h"

StarfruitFruit::StarfruitFruit() 
{
}

StarfruitFruit::~StarfruitFruit() 
{
}

void StarfruitFruit::Start()
{
	IndexNum_ = 7;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_STARFRUIT_FRUIT);
}