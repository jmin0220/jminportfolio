#include "ItemTable.h"


int StringtoItemTable(std::string _Name)
{
	if (ITEM_NAME_EMPTY == _Name)
	{
		return (int)ITEMTABLE::EMPTY;
	}

	/// 도구 /////////////////////////////////////////////////////////
	if (ITEM_NAME_HOE == _Name)
	{
		return (int)ITEMTABLE::HOE;
	}
	if (ITEM_NAME_AXE == _Name)
	{
		return (int)ITEMTABLE::AXE;
	}
	if (ITEM_NAME_WATERINGCAN == _Name)
	{
		return (int)ITEMTABLE::WATERINGCAN;
	}


	/// 나무 /////////////////////////////////////////////////////////
	if (ITEM_NAME_OAKTREE == _Name)
	{
		return (int)ITEMTABLE::OAKTREE;
	}
	if (ITEM_NAME_MAPLETREE == _Name)
	{
		return (int)ITEMTABLE::MAPLETREE;
	}
	if (ITEM_NAME_PINETREE == _Name)
	{
		return (int)ITEMTABLE::PINETREE;
	}


	/// 농작물 /////////////////////////////////////////////////////////
	if (ITEM_NAME_PARSNIP == _Name)
	{
		return (int)ITEMTABLE::PARSNIP;
	}
	if (ITEM_NAME_COULIFLOWER == _Name)
	{
		return (int)ITEMTABLE::COULIFLOWER;
	}
	if (ITEM_NAME_GARLIC == _Name)
	{
		return (int)ITEMTABLE::GARLIC;
	}
	if (ITEM_NAME_RHUBARB == _Name)
	{
		return (int)ITEMTABLE::RHUBARB;
	}
	if (ITEM_NAME_TOMATO == _Name)
	{
		return (int)ITEMTABLE::TOMATO;
	}
	if (ITEM_NAME_HOTPEPPER == _Name)
	{
		return (int)ITEMTABLE::HOTPEPPER;
	}
	if (ITEM_NAME_RADISH == _Name)
	{
		return (int)ITEMTABLE::RADISH;
	}
	if (ITEM_NAME_STARFRUIT == _Name)
	{
		return (int)ITEMTABLE::STARFRUIT;
	}
	if (ITEM_NAME_EGGPLANT == _Name)
	{
		return (int)ITEMTABLE::EGGPLANT;
	}
	if (ITEM_NAME_PUMPKIN == _Name)
	{
		return (int)ITEMTABLE::PUMPKIN;
	}
	if (ITEM_NAME_YAM == _Name)
	{
		return (int)ITEMTABLE::YAM;
	}
	if (ITEM_NAME_BEET == _Name)
	{
		return (int)ITEMTABLE::BEET;
	}
	if (ITEM_NAME_SUNFLOWER == _Name)
	{
		return (int)ITEMTABLE::SUNFLOWER;
	}
	if (ITEM_NAME_GREENBEAN == _Name)
	{
		return (int)ITEMTABLE::GREENBEAN;
	}
	if (ITEM_NAME_POTATO == _Name)
	{
		return (int)ITEMTABLE::POTATO;
	}
	if (ITEM_NAME_KALE == _Name)
	{
		return (int)ITEMTABLE::KALE;
	}
	if (ITEM_NAME_MELON == _Name)
	{
		return (int)ITEMTABLE::MELON;
	}
	if (ITEM_NAME_BLUEBERRY == _Name)
	{
		return (int)ITEMTABLE::BLUEBERRY;
	}
	if (ITEM_NAME_REDCABBAGE == _Name)
	{
		return (int)ITEMTABLE::REDCABBAGE;
	}
	if (ITEM_NAME_CORN == _Name)
	{
		return (int)ITEMTABLE::CORN;
	}


	/// 나무 아이템 /////////////////////////////////////////////////////
	if (ITEM_NAME_MINITREE == _Name)
	{
		return (int)ITEMTABLE::MINITREE;
	}


	/// 물고기 /////////////////////////////////////////////////////
	if (ITEM_NAME_PUFFERFISH == _Name)
	{
		return (int)ITEMTABLE::PUFFERFISH;
	}
	if (ITEM_NAME_TUNA == _Name)
	{
		return (int)ITEMTABLE::TUNA;
	}
	if (ITEM_NAME_ANCHOVY == _Name)
	{
		return (int)ITEMTABLE::ANCHOVY;
	}

	/// 열매 /////////////////////////////////////////////////////
	if (ITEM_NAME_PARSNIP_FRUIT == _Name)
	{
		return (int)ITEMTABLE::PARSNIP_FRUIT;
	}
	if (ITEM_NAME_COULIFLOWER_FRUIT == _Name)
	{
		return (int)ITEMTABLE::COULIFLOWER_FRUIT;
	}
	if (ITEM_NAME_GARLIC_FRUIT == _Name)
	{
		return (int)ITEMTABLE::GARLIC_FRUIT;
	}
	if (ITEM_NAME_RHUBARB_FRUIT == _Name)
	{
		return (int)ITEMTABLE::RHUBARB_FRUIT;
	}
	if (ITEM_NAME_TOMATO_FRUIT == _Name)
	{
		return (int)ITEMTABLE::TOMATO_FRUIT;
	}
	if (ITEM_NAME_HOTPEPPER_FRUIT == _Name)
	{
		return (int)ITEMTABLE::HOTPEPPER_FRUIT;
	}
	if (ITEM_NAME_RADISH_FRUIT == _Name)
	{
		return (int)ITEMTABLE::RADISH_FRUIT;
	}
	if (ITEM_NAME_STARFRUIT == _Name)
	{
		return (int)ITEMTABLE::STARFRUIT_FRUIT;
	}
	if (ITEM_NAME_EGGPLANT_FRUIT == _Name)
	{
		return (int)ITEMTABLE::EGGPLANT_FRUIT;
	}
	if (ITEM_NAME_PUMPKIN_FRUIT == _Name)
	{
		return (int)ITEMTABLE::PUMPKIN_FRUIT;
	}
	if (ITEM_NAME_YAM_FRUIT == _Name)
	{
		return (int)ITEMTABLE::YAM_FRUIT;
	}
	if (ITEM_NAME_BEET_FRUIT == _Name)
	{
		return (int)ITEMTABLE::BEET_FRUIT;
	}
	if (ITEM_NAME_SUNFLOWER_FRUIT == _Name)
	{
		return (int)ITEMTABLE::SUNFLOWER_FRUIT;
	}
	if (ITEM_NAME_GREENBEAN_FRUIT == _Name)
	{
		return (int)ITEMTABLE::GREENBEAN_FRUIT;
	}
	if (ITEM_NAME_POTATO_FRUIT == _Name)
	{
		return (int)ITEMTABLE::POTATO_FRUIT;
	}
	if (ITEM_NAME_KALE_FRUIT == _Name)
	{
		return (int)ITEMTABLE::KALE_FRUIT;
	}
	if (ITEM_NAME_MELON_FRUIT == _Name)
	{
		return (int)ITEMTABLE::MELON_FRUIT;
	}
	if (ITEM_NAME_BLUEBERRY_FRUIT == _Name)
	{
		return (int)ITEMTABLE::BLUEBERRY_FRUIT;
	}
	if (ITEM_NAME_REDCABBAGE_FRUIT == _Name)
	{
		return (int)ITEMTABLE::REDCABBAGE_FRUIT;
	}
	if (ITEM_NAME_CORN_FRUIT == _Name)
	{
		return (int)ITEMTABLE::CORN_FRUIT;
	}

	/// 광석 /////////////////////////////////////////////////////
	if (ITEM_NAME_DIAMOND == _Name)
	{
		return (int)ITEMTABLE::DIAMOND;
	}
	if (ITEM_NAME_RUBY == _Name)
	{
		return (int)ITEMTABLE::RUBY;
	}
	if (ITEM_NAME_JADE == _Name)
	{
		return (int)ITEMTABLE::JADE;
	}
	if (ITEM_NAME_AMETHYST == _Name)
	{
		return (int)ITEMTABLE::AMETHYST;
	}
	if (ITEM_NAME_TOPAZ == _Name)
	{
		return (int)ITEMTABLE::TOPAZ;
	}

	// Default
	return (int)ITEMTABLE::EMPTY;
}