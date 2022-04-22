#include "Item.h"
#include "ItemTable.h"
#include "ContentsEnums.h"

Item::Item() 
	: ClickedFlg(false)
{
	ItemName_ = "Empty";
}

Item::~Item() 
{
}

void Item::Start()
{
}

void Item::SetIconRendererInfo(int _ItemNum)
{
	switch (_ItemNum)
	{
	case (int)ITEMTABLE::EMPTY:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		IndexNum_ = -1;
		ItemName_ = ITEM_NAME_EMPTY;
		break;
	case (int)ITEMTABLE::HOE:
		IconRenderer_->SetImage(IMAGE_TOOL_ICON);
		IndexNum_ = 0;
		ItemName_ = ITEM_NAME_HOE;
		break;
	case (int)ITEMTABLE::AXE:
		IconRenderer_->SetImage(IMAGE_TOOL_ICON);
		IndexNum_ = 1;
		ItemName_ = ITEM_NAME_AXE;
		break;
	case (int)ITEMTABLE::WATERINGCAN:
		IconRenderer_->SetImage(IMAGE_TOOL_ICON);
		IndexNum_ = 2;
		ItemName_ = ITEM_NAME_WATERINGCAN;
		break;
	/// 나무 ///////////////////////////////////////////////////////////////
	case (int)ITEMTABLE::OAKTREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 30;
		ItemName_ = ITEM_NAME_OAKTREE;
		break;
	case (int)ITEMTABLE::MAPLETREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 31;
		ItemName_ = ITEM_NAME_MAPLETREE;
		break;
	case (int)ITEMTABLE::PINETREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 32;
		ItemName_ = ITEM_NAME_PINETREE;
		break;

	/// 농작물(Crops) ///////////////////////////////////////////////////////
	case (int)ITEMTABLE::PARSNIP:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 0;
		ItemName_ = ITEM_NAME_PARSNIP;
		break;
	case (int)ITEMTABLE::COULIFLOWER:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 1;
		ItemName_ = ITEM_NAME_COULIFLOWER;
		break;
	case (int)ITEMTABLE::GARLIC:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 2;
		ItemName_ = ITEM_NAME_GARLIC;
		break;
	case (int)ITEMTABLE::RHUBARB:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 3;
		ItemName_ = ITEM_NAME_RHUBARB;
		break;
	case (int)ITEMTABLE::TOMATO:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 4;
		ItemName_ = ITEM_NAME_TOMATO;
		break;
	case (int)ITEMTABLE::HOTPEPPER:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 5;
		ItemName_ = ITEM_NAME_HOTPEPPER;
		break;
	case (int)ITEMTABLE::RADISH:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 6;
		ItemName_ = ITEM_NAME_RADISH;
		break;
	case (int)ITEMTABLE::STARFRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 7;
		ItemName_ = ITEM_NAME_STARFRUIT;
		break;
	case (int)ITEMTABLE::EGGPLANT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 8;
		ItemName_ = ITEM_NAME_EGGPLANT;
		break;
	case (int)ITEMTABLE::PUMPKIN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 9;
		ItemName_ = ITEM_NAME_PUMPKIN;
		break;
	case (int)ITEMTABLE::YAM:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 10;
		ItemName_ = ITEM_NAME_YAM;
		break;
	case (int)ITEMTABLE::BEET:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 11;
		ItemName_ = ITEM_NAME_BEET;
		break;
	case (int)ITEMTABLE::SUNFLOWER:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 12;
		ItemName_ = ITEM_NAME_SUNFLOWER;
		break;
	case (int)ITEMTABLE::GREENBEAN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 13;
		ItemName_ = ITEM_NAME_GREENBEAN;
		break;
	case (int)ITEMTABLE::POTATO:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 14;
		ItemName_ = ITEM_NAME_POTATO;
		break;
	case (int)ITEMTABLE::KALE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 15;
		ItemName_ = ITEM_NAME_KALE;
		break;
	case (int)ITEMTABLE::MELON:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 16;
		ItemName_ = ITEM_NAME_MELON;
		break;
	case (int)ITEMTABLE::BLUEBERRY:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 17;
		ItemName_ = ITEM_NAME_BLUEBERRY;
		break;
	case (int)ITEMTABLE::REDCABBAGE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 18;
		ItemName_ = ITEM_NAME_REDCABBAGE;
		break;
	case (int)ITEMTABLE::CORN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 19;
		ItemName_ = ITEM_NAME_CORN;
		break;

	/// 물고기 /////////////////////////////////////////////////////////////
	case (int)ITEMTABLE::PUFFERFISH:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FISHING);
		IndexNum_ = 0;
		ItemName_ = ITEM_NAME_PUFFERFISH;
		break;
	case (int)ITEMTABLE::ANCHOVY:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FISHING);
		IndexNum_ = 1;
		ItemName_ = ITEM_NAME_ANCHOVY;
		break;
	case (int)ITEMTABLE::TUNA:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FISHING);
		IndexNum_ = 2;
		ItemName_ = ITEM_NAME_TUNA;
		break;

	/// 나무에서 발생한 아이템  ////////////////////////////////////////
	case (int)ITEMTABLE::MINITREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 39;
		ItemName_ = ITEM_NAME_MINITREE;
		break;
	/// 농작물(Crops)에서 발생한 아이템  //////////////////////////////
	case (int)ITEMTABLE::PARSNIP_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 0;
		ItemName_ = ITEM_NAME_PARSNIP_FRUIT;
		break;
	case (int)ITEMTABLE::COULIFLOWER_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 1;
		ItemName_ = ITEM_NAME_COULIFLOWER_FRUIT;
		break;
	case (int)ITEMTABLE::GARLIC_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 2;
		ItemName_ = ITEM_NAME_GARLIC_FRUIT;
		break;
	case (int)ITEMTABLE::RHUBARB_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 3;
		ItemName_ = ITEM_NAME_RHUBARB_FRUIT;
		break;
	case (int)ITEMTABLE::TOMATO_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 4;
		ItemName_ = ITEM_NAME_TOMATO_FRUIT;
		break;
	case (int)ITEMTABLE::HOTPEPPER_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 5;
		ItemName_ = ITEM_NAME_HOTPEPPER_FRUIT;
		break;
	case (int)ITEMTABLE::RADISH_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 6;
		ItemName_ = ITEM_NAME_RADISH_FRUIT;
		break;
	case (int)ITEMTABLE::STARFRUIT_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 7;
		ItemName_ = ITEM_NAME_STARFRUIT_FRUIT;
		break;
	case (int)ITEMTABLE::EGGPLANT_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 8;
		ItemName_ = ITEM_NAME_EGGPLANT_FRUIT;
		break;
	case (int)ITEMTABLE::PUMPKIN_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 9;
		ItemName_ = ITEM_NAME_PUMPKIN_FRUIT;
		break;
	case (int)ITEMTABLE::YAM_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 10;
		ItemName_ = ITEM_NAME_YAM_FRUIT;
		break;
	case (int)ITEMTABLE::BEET_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 11;
		ItemName_ = ITEM_NAME_BEET_FRUIT;
		break;
	case (int)ITEMTABLE::SUNFLOWER_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 12;
		ItemName_ = ITEM_NAME_SUNFLOWER_FRUIT;
		break;
	case (int)ITEMTABLE::GREENBEAN_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 13;
		ItemName_ = ITEM_NAME_GREENBEAN_FRUIT;
		break;
	case (int)ITEMTABLE::POTATO_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 14;
		ItemName_ = ITEM_NAME_POTATO_FRUIT;
		break;
	case (int)ITEMTABLE::KALE_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 15;
		ItemName_ = ITEM_NAME_KALE_FRUIT;
		break;
	case (int)ITEMTABLE::MELON_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 16;
		ItemName_ = ITEM_NAME_MELON_FRUIT;
		break;
	case (int)ITEMTABLE::BLUEBERRY_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 17;
		ItemName_ = ITEM_NAME_BLUEBERRY_FRUIT;
		break;
	case (int)ITEMTABLE::REDCABBAGE_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 18;
		ItemName_ = ITEM_NAME_REDCABBAGE_FRUIT;
		break;
	case (int)ITEMTABLE::CORN_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 19;
		ItemName_ = ITEM_NAME_CORN_FRUIT;
		break;
	default:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		IndexNum_ = -1;
		ItemName_ = ITEM_NAME_EMPTY;
		break;
	}

	// IndexNum_ == -1 ->이미지가 잘려져있지 않음
	if (IndexNum_ != -1)
	{
		IconRenderer_->SetIndex(IndexNum_);
	}
}