#include "ParsnipFruit.h"
#include "ContentsEnums.h"

ParsnipFruit::ParsnipFruit()
{
}

ParsnipFruit::~ParsnipFruit()
{
}

void ParsnipFruit::Start()
{
	IndexNum_ = 0;

	SetItemRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_PARSNIP_FRUIT);
	SetIconRenderer(*CreateRenderer(IMAGE_ENVIRONMENT_FRUIT, (int)ORDER::FRONTA));
	GetIconRenderer().SetIndex(IndexNum_);
	GetIconRenderer().Off();
}