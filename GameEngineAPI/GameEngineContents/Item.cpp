#include "Item.h"
#include "ItemTable.h"
#include "ContentsEnums.h"

Item::Item() 
	: ClickedFlg(false)
	, Countable(false)
{
	ItemName_ = "Empty";
}

Item::~Item() 
{
}

void Item::Start()
{
}

void Item::SetItemNum()
{
	if (true == Countable)
	{
		float PosX = IconRenderer_->GetPivot().x + 5;
		float PosY = IconRenderer_->GetPivot().y + 17;
		for (int i = Counter_.size(); i > 0; i--)
		{
			Font_[i - 1]->RendererFontOn();
			Font_[i - 1]->GetFont(Counter_[i - 1]);
			Font_[i - 1]->GetRendererFont()->SetPivot({ PosX + (11 * i)
				                                      , PosY});
		}
	}
}


void Item::SetItemNum(int _Order)
{
	SetItemNum();

	if (true == Countable)
	{
		for (int i = Counter_.size(); i > 0; i--)
		{
			Font_[i - 1]->GetRendererFont()->SetOrder(_Order);
		}
	}
}

void Item::AddCounter()
{
	if (true == Countable && stoi(Counter_) < 99)
	{
		Counter_ = std::to_string(stoi(Counter_) + 1);
	}
}

void Item::SubCounter()
{
	if (true == Countable)
	{
		Counter_ = std::to_string(stoi(Counter_) - 1);
	}
}

void Item::SetIconRendererInfo(int _ItemNum)
{
	switch (_ItemNum)
	{
	case (int)ITEMTABLE::EMPTY:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		IndexNum_ = -1;
		Countable = false;
		ItemName_ = ITEM_NAME_EMPTY;
		break;
	case (int)ITEMTABLE::HOE:
		IconRenderer_->SetImage(IMAGE_TOOL_ICON);
		IndexNum_ = 0;
		Countable = false;
		ItemName_ = ITEM_NAME_HOE;
		break;
	case (int)ITEMTABLE::AXE:
		IconRenderer_->SetImage(IMAGE_TOOL_ICON);
		IndexNum_ = 1;
		Countable = false;
		ItemName_ = ITEM_NAME_AXE;
		break;
	case (int)ITEMTABLE::WATERINGCAN:
		IconRenderer_->SetImage(IMAGE_TOOL_ICON);
		IndexNum_ = 2;
		Countable = false;
		ItemName_ = ITEM_NAME_WATERINGCAN;
		break;
	case (int)ITEMTABLE::FISHINGROD:
		IconRenderer_->SetImage(IMAGE_TOOL_ICON);
		IndexNum_ = 3;
		Countable = false;
		ItemName_ = ITEM_NAME_FISHINGROD;
		break;
	/// ���� ///////////////////////////////////////////////////////////////
	case (int)ITEMTABLE::OAKTREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 30;
		Countable = true;
		ItemName_ = ITEM_NAME_OAKTREE;
		break;
	case (int)ITEMTABLE::MAPLETREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 31;
		Countable = true;
		ItemName_ = ITEM_NAME_MAPLETREE;
		break;
	case (int)ITEMTABLE::PINETREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 32;
		Countable = true;
		ItemName_ = ITEM_NAME_PINETREE;
		break;

	/// ���۹�(Crops) ///////////////////////////////////////////////////////
	case (int)ITEMTABLE::PARSNIP:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 0;
		Countable = true;
		ItemName_ = ITEM_NAME_PARSNIP;
		break;
	case (int)ITEMTABLE::COULIFLOWER:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 1;
		Countable = true;
		ItemName_ = ITEM_NAME_COULIFLOWER;
		break;
	case (int)ITEMTABLE::GARLIC:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 2;
		Countable = true;
		ItemName_ = ITEM_NAME_GARLIC;
		break;
	case (int)ITEMTABLE::RHUBARB:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 3;
		Countable = true;
		ItemName_ = ITEM_NAME_RHUBARB;
		break;
	case (int)ITEMTABLE::TOMATO:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 4;
		Countable = true;
		ItemName_ = ITEM_NAME_TOMATO;
		break;
	case (int)ITEMTABLE::HOTPEPPER:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 5;
		Countable = true;
		ItemName_ = ITEM_NAME_HOTPEPPER;
		break;
	case (int)ITEMTABLE::RADISH:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 6;
		Countable = true;
		ItemName_ = ITEM_NAME_RADISH;
		break;
	case (int)ITEMTABLE::STARFRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 7;
		Countable = true;
		ItemName_ = ITEM_NAME_STARFRUIT;
		break;
	case (int)ITEMTABLE::EGGPLANT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 8;
		Countable = true;
		ItemName_ = ITEM_NAME_EGGPLANT;
		break;
	case (int)ITEMTABLE::PUMPKIN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 9;
		Countable = true;
		ItemName_ = ITEM_NAME_PUMPKIN;
		break;
	case (int)ITEMTABLE::YAM:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 10;
		Countable = true;
		ItemName_ = ITEM_NAME_YAM;
		break;
	case (int)ITEMTABLE::BEET:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 11;
		Countable = true;
		ItemName_ = ITEM_NAME_BEET;
		break;
	case (int)ITEMTABLE::SUNFLOWER:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 12;
		Countable = true;
		ItemName_ = ITEM_NAME_SUNFLOWER;
		break;
	case (int)ITEMTABLE::GREENBEAN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 13;
		Countable = true;
		ItemName_ = ITEM_NAME_GREENBEAN;
		break;
	case (int)ITEMTABLE::POTATO:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 14;
		Countable = true;
		ItemName_ = ITEM_NAME_POTATO;
		break;
	case (int)ITEMTABLE::KALE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 15;
		Countable = true;
		ItemName_ = ITEM_NAME_KALE;
		break;
	case (int)ITEMTABLE::MELON:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 16;
		Countable = true;
		ItemName_ = ITEM_NAME_MELON;
		break;
	case (int)ITEMTABLE::BLUEBERRY:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 17;
		Countable = true;
		ItemName_ = ITEM_NAME_BLUEBERRY;
		break;
	case (int)ITEMTABLE::REDCABBAGE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 18;
		Countable = true;
		ItemName_ = ITEM_NAME_REDCABBAGE;
		break;
	case (int)ITEMTABLE::CORN:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_SEED);
		IndexNum_ = 19;
		Countable = true;
		ItemName_ = ITEM_NAME_CORN;
		break;

	/// ����� /////////////////////////////////////////////////////////////
	case (int)ITEMTABLE::PUFFERFISH:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FISHING);
		IndexNum_ = 0;
		Countable = true;
		ItemName_ = ITEM_NAME_PUFFERFISH;
		break;
	case (int)ITEMTABLE::ANCHOVY:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FISHING);
		IndexNum_ = 1;
		Countable = true;
		ItemName_ = ITEM_NAME_ANCHOVY;
		break;
	case (int)ITEMTABLE::TUNA:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FISHING);
		IndexNum_ = 2;
		Countable = true;
		ItemName_ = ITEM_NAME_TUNA;
		break;

	/// �������� �߻��� ������  ////////////////////////////////////////
	case (int)ITEMTABLE::MINITREE:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FORAGE);
		IndexNum_ = 39;
		Countable = true;
		ItemName_ = ITEM_NAME_MINITREE;
		break;
	/// ���۹�(Crops)���� �߻��� ������  //////////////////////////////
	case (int)ITEMTABLE::PARSNIP_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 0;
		Countable = true;
		ItemName_ = ITEM_NAME_PARSNIP_FRUIT;
		break;
	case (int)ITEMTABLE::COULIFLOWER_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 1;
		Countable = true;
		ItemName_ = ITEM_NAME_COULIFLOWER_FRUIT;
		break;
	case (int)ITEMTABLE::GARLIC_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 2;
		Countable = true;
		ItemName_ = ITEM_NAME_GARLIC_FRUIT;
		break;
	case (int)ITEMTABLE::RHUBARB_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 3;
		Countable = true;
		ItemName_ = ITEM_NAME_RHUBARB_FRUIT;
		break;
	case (int)ITEMTABLE::TOMATO_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 4;
		Countable = true;
		ItemName_ = ITEM_NAME_TOMATO_FRUIT;
		break;
	case (int)ITEMTABLE::HOTPEPPER_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 5;
		Countable = true;
		ItemName_ = ITEM_NAME_HOTPEPPER_FRUIT;
		break;
	case (int)ITEMTABLE::RADISH_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 6;
		Countable = true;
		ItemName_ = ITEM_NAME_RADISH_FRUIT;
		break;
	case (int)ITEMTABLE::STARFRUIT_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 7;
		Countable = true;
		ItemName_ = ITEM_NAME_STARFRUIT_FRUIT;
		break;
	case (int)ITEMTABLE::EGGPLANT_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 8;
		Countable = true;
		ItemName_ = ITEM_NAME_EGGPLANT_FRUIT;
		break;
	case (int)ITEMTABLE::PUMPKIN_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 9;
		Countable = true;
		ItemName_ = ITEM_NAME_PUMPKIN_FRUIT;
		break;
	case (int)ITEMTABLE::YAM_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 10;
		Countable = true;
		ItemName_ = ITEM_NAME_YAM_FRUIT;
		break;
	case (int)ITEMTABLE::BEET_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 11;
		Countable = true;
		ItemName_ = ITEM_NAME_BEET_FRUIT;
		break;
	case (int)ITEMTABLE::SUNFLOWER_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 12;
		Countable = true;
		ItemName_ = ITEM_NAME_SUNFLOWER_FRUIT;
		break;
	case (int)ITEMTABLE::GREENBEAN_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 13;
		Countable = true;
		ItemName_ = ITEM_NAME_GREENBEAN_FRUIT;
		break;
	case (int)ITEMTABLE::POTATO_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 14;
		Countable = true;
		ItemName_ = ITEM_NAME_POTATO_FRUIT;
		break;
	case (int)ITEMTABLE::KALE_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 15;
		Countable = true;
		ItemName_ = ITEM_NAME_KALE_FRUIT;
		break;
	case (int)ITEMTABLE::MELON_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 16;
		Countable = true;
		ItemName_ = ITEM_NAME_MELON_FRUIT;
		break;
	case (int)ITEMTABLE::BLUEBERRY_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 17;
		Countable = true;
		ItemName_ = ITEM_NAME_BLUEBERRY_FRUIT;
		break;
	case (int)ITEMTABLE::REDCABBAGE_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 18;
		Countable = true;
		ItemName_ = ITEM_NAME_REDCABBAGE_FRUIT;
		break;
	case (int)ITEMTABLE::CORN_FRUIT:
		IconRenderer_->SetImage(IMAGE_ENVIRONMENT_FRUIT);
		IndexNum_ = 19;
		Countable = true;
		ItemName_ = ITEM_NAME_CORN_FRUIT;
		break;


	/// �������� �߻��� ������  //////////////////////////////
	case (int)ITEMTABLE::DIAMOND:
		IconRenderer_->SetImage(IMAGE_ITEM_MINERAL);
		IndexNum_ = 0;
		Countable = true;
		ItemName_ = ITEM_NAME_DIAMOND;
		break;
	case (int)ITEMTABLE::RUBY:
		IconRenderer_->SetImage(IMAGE_ITEM_MINERAL);
		IndexNum_ = 1;
		Countable = true;
		ItemName_ = ITEM_NAME_RUBY;
		break;
	case (int)ITEMTABLE::JADE:
		IconRenderer_->SetImage(IMAGE_ITEM_MINERAL);
		IndexNum_ = 2;
		Countable = true;
		ItemName_ = ITEM_NAME_JADE;
		break;
	case (int)ITEMTABLE::AMETHYST:
		IconRenderer_->SetImage(IMAGE_ITEM_MINERAL);
		IndexNum_ = 3;
		Countable = true;
		ItemName_ = ITEM_NAME_AMETHYST;
		break;
	case (int)ITEMTABLE::TOPAZ:
		IconRenderer_->SetImage(IMAGE_ITEM_MINERAL);
		IndexNum_ = 4;
		Countable = true;
		ItemName_ = ITEM_NAME_TOPAZ;
		break;


	default:
		IconRenderer_->SetImage(IMAGE_INVENTORY_EMPTY);
		IndexNum_ = -1;
		Countable = false;
		ItemName_ = ITEM_NAME_EMPTY;
		break;
	}

	// IndexNum_ == -1 ->�̹����� �߷������� ����
	if (IndexNum_ != -1)
	{
		IconRenderer_->SetIndex(IndexNum_);
	}
}