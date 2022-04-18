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
	case (int)ITEMTABLE::PARSNIP:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 0;
		ItemName_ = ITEM_NAME_PARSNIP;
		break;
	case (int)ITEMTABLE::POTATO:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 14;
		ItemName_ = ITEM_NAME_POTATO;
		break;
	case (int)ITEMTABLE::CORN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 19;
		ItemName_ = ITEM_NAME_CORN;
		break;
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
	default:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		ItemName_ = ITEM_NAME_EMPTY;
		break;
	}

	IconRenderer_->SetIndex(IndexNum_);
}