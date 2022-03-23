#include "InventoryBar.h"

// 인벤토리는 이렇게 만드는게 아닌듯
InventoryBar::InventoryBar() 
{
}

InventoryBar::~InventoryBar() 
{
}

void InventoryBar::Start()
{
	// InventoryBar인터페이스렌더링
	// 상단
	SetPosition({ 640, 55 });
	//하단
	//SetPosition({ 640, 663 });
	CreateRenderer("InventoryBar.bmp");
}