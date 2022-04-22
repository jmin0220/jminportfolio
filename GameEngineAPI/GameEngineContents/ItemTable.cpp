#include "ItemTable.h"


int StringtoItemTable(std::string _Name)
{
	if (ITEM_NAME_EMPTY == _Name)
	{
		return (int)ITEMTABLE::EMPTY;
	}
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
	if (ITEM_NAME_PARSNIP == _Name)
	{
		return (int)ITEMTABLE::PARSNIP;
	}
	if (ITEM_NAME_POTATO == _Name)
	{
		return (int)ITEMTABLE::POTATO;
	}
	if (ITEM_NAME_CORN == _Name)
	{
		return (int)ITEMTABLE::CORN;
	}
	if (ITEM_NAME_MINITREE == _Name)
	{
		return (int)ITEMTABLE::MINITREE;
	}

	// Default
	return (int)ITEMTABLE::EMPTY;
}