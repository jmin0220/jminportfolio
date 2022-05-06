#include "Amethyst.h"
#include "ContentsEnums.h"

Amethyst::Amethyst() 
{
}

Amethyst::~Amethyst() 
{
}

void Amethyst::Start()
{
	IndexNum_ = 3;

	SetItemRenderer(*CreateRenderer(IMAGE_ITEM_MINERAL, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_AMETHYST);
}