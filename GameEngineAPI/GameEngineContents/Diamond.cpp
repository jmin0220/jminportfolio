#include "Diamond.h"
#include "ContentsEnums.h"

Diamond::Diamond() 
{
}

Diamond::~Diamond() 
{
}

void Diamond::Start()
{
	IndexNum_ = 0;

	SetItemRenderer(*CreateRenderer(IMAGE_ITEM_MINERAL, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_DIAMOND);
}