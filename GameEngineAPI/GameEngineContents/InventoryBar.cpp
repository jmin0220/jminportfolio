#include "InventoryBar.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

// �κ��丮�� �̷��� ����°� �ƴѵ�
InventoryBar::InventoryBar() 
{
}

InventoryBar::~InventoryBar() 
{
}

void InventoryBar::Start()
{
	// InventoryBar�������̽�������
	// ���͸� �߾ӿ� ��ġ
	SetPosition({0, 0});

	GameEngineRenderer* Renderer = CreateRenderer("InventoryBar.bmp");
	
	// ������ �׸��� �������Ǵ� ��
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