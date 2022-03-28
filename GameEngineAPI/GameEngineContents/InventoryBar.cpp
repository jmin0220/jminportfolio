#include "InventoryBar.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>

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
	SetPosition({ IMAGE_INVENTORYBAR_POS_UP_W, IMAGE_INVENTORYBAR_POS_UP_H });
	//하단
	//SetPosition({ IMAGE_INVENTORYBAR_POS_DOWN_W, IMAGE_INVENTORYBAR_POS_DOWN_H });
	CreateRenderer("InventoryBar.bmp");


	// 아이콘의 크기는 약 3.6배?
}