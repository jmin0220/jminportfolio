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
}



/*
Parsnip
Couliflower
Garlic
Rhubarb
Tomato
HotPepper
Radish
Starfruit
Eggplant
Pumpkin
Yam
Beet
Sunflower
GreenBean
Potato	6
Kale	5
Melon	6
Blueberry	7
RedCabbage	6
Corn	7
*/