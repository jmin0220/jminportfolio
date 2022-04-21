#include "MiniTree.h"
#include "ContentsEnums.h"

MiniTree::MiniTree() 
{
}

MiniTree::~MiniTree() 
{
}

void MiniTree::Start()
{
	IndexNum_ = 39;

	SetItemRenderer(*CreateRenderer(IMAGE_ITEM_FORAGE, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_MINITREE);
	SetIconRenderer(*CreateRenderer(IMAGE_ITEM_FORAGE, (int)ORDER::FRONTA));
	GetIconRenderer().SetIndex(IndexNum_);
	GetIconRenderer().Off();
}