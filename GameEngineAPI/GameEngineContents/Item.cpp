#include "Item.h"
#include "ItemTable.h"
#include "ContentsEnums.h"

Item::Item() 
{
	ItemName_ = "Empty";
}

Item::~Item() 
{
}

void Item::Start()
{
}

void Item::SetIconRenderer(int _ItemNum)
{
	switch (_ItemNum)
	{
	case (int)ITEMTABLE::EMPTY:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		ItemName_ = ITEM_NAME_EMPTY;
		break;
	case (int)ITEMTABLE::HOE:
		IconRenderer_->SetImage(IMAGE_TOOL_SET1);
		IconRenderer_->SetIndex(5);
		ItemName_ = ITEM_NAME_HOE;
		break;
	case (int)ITEMTABLE::AXE:
		IconRenderer_->SetImage(IMAGE_TOOL_SET1);
		IconRenderer_->SetIndex(89);
		ItemName_ = ITEM_NAME_AXE;
		break;
	case (int)ITEMTABLE::SYTHE:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		// ItemName_ = ITEM_NAME_EMPTY;
		break;
	case (int)ITEMTABLE::WATERINGCAN:
		IconRenderer_->SetImage(IMAGE_TOOL_SET2);
		IconRenderer_->SetIndex(2);
		ItemName_ = ITEM_NAME_WATERINGCAN;
		break;
	case (int)ITEMTABLE::OAKTREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IconRenderer_->SetIndex(30);
		break;
	case (int)ITEMTABLE::MAPLETREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IconRenderer_->SetIndex(31);
		break;
	case (int)ITEMTABLE::PINETREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IconRenderer_->SetIndex(32);
		break;
	case (int)ITEMTABLE::PARSNIP:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		break;
	case (int)ITEMTABLE::POTATO:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		break;
	case (int)ITEMTABLE::CORN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		break;
	case (int)ITEMTABLE::PUFFERFISH:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		break;
	case (int)ITEMTABLE::TUNA:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		break;
	case (int)ITEMTABLE::ANCHOVY:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		break;
	default:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		break;
	}
}