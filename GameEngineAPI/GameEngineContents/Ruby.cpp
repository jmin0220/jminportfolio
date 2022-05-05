#include "Ruby.h"
#include "ContentsEnums.h"

Ruby::Ruby() 
{
}

Ruby::~Ruby() 
{
}

void Ruby::Start()
{
	IndexNum_ = 2;

	SetItemRenderer(*CreateRenderer(IMAGE_ITEM_MINERAL, (int)ORDER::FRONTA));
	GetItemRenderer().SetIndex(IndexNum_);
	SetItemName(ITEM_NAME_RUBY);
}