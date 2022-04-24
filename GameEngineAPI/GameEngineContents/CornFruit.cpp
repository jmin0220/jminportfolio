#include "CornFruit.h"
#include "ContentsEnums.h"

CornFruit::CornFruit() 
{
}

CornFruit::~CornFruit() 
{
}

void CornFruit::Start()
{
	IndexNum_ = 19;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_CORN_FRUIT);
}