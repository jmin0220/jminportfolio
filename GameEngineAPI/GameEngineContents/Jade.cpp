#include "Jade.h"
#include "ContentsEnums.h"

Jade::Jade() 
{
}

Jade::~Jade() 
{
}

void Jade::Start()
{
	IndexNum_ = 2;

	SetItemRenderer(*CreateRenderer(IMAGE_ITEM_MINERAL, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_JADE);
}

