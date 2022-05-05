#include "Topaz.h"
#include "ContentsEnums.h"

Topaz::Topaz() 
{
}

Topaz::~Topaz() 
{
}

void Topaz::Start()
{
	IndexNum_ = 8;

	SetItemRenderer(*CreateRenderer(IMAGE_ITEM_MINERAL, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_TOPAZ);
}