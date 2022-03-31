#include "InventoryBar.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

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
	// 액터를 중앙에 배치
	SetPosition({0, 0});

	GameEngineRenderer* Renderer = CreateRenderer("InventoryBar.bmp");
	
	// 실제로 그림이 렌더링되는 곳
	Renderer->SetPivot({ IMAGE_INVENTORYBAR_POS_UP_X, IMAGE_INVENTORYBAR_POS_UP_Y });
	Renderer->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });
	Renderer->CameraEffectOff();
}

void InventoryBar::Update()
{

}

void InventoryBar::SetPos(float4 _Pos)
{

}