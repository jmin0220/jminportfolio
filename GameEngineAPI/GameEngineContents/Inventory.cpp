#include "Inventory.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Hoe.h"
#include "Axe.h"
#include "Sythe.h"

Inventory::Inventory() 
	: RendererInven_(nullptr)
	, RendererSelectBox_(nullptr)
	, SelectBoxHotkey_(0)
	, ExtendFlg(false)
{
}

Inventory::~Inventory() 
{
	for (size_t i = 0; i < 36; i++)
	{
		if (nullptr != InventoryList_[i])
		{
			delete InventoryList_[i];
			InventoryList_[i] = nullptr;
		}
	}
}

void Inventory::Start()
{
	// InventoryBar인터페이스렌더링
	// 액터를 중앙에 배치
	SetPosition({0, 0});

	RendererInven_ = CreateRenderer(IMAGE_INVENTORY_BAR);
	RendererSelectBox_ = CreateRenderer(IMAGE_INVENTORY_SELECT);
	
	// 실제로 그림이 렌더링되는 곳
	// RendererBar_->SetPivot({ IMAGE_INVENTORYBAR_POS_UP_X, IMAGE_INVENTORYBAR_POS_UP_Y });
	RendererInven_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });
	RendererSelectBox_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)SelectBoxHotkey_)), IMAGE_INVENTORYBAR_POS_DOWN_Y});

	RendererInven_->CameraEffectOff();
	RendererSelectBox_->CameraEffectOff();

	InitKey();



	for (size_t i = 0; i < 12; i++)
	{
		// 인벤에 아이템의 정보를 집어넣음.
		// 아이콘은 아이템과 별개로 넣어야하는가?
		// 중복되는 아이템의 갯수는?
		// 
		InventoryList_[i] = new Item();
		// 이부분도 다시 생각해봐야할듯
		InventoryList_[i]->SetIconRenderer(*CreateRenderer("Empty.bmp", (int)ORDER::UIICONS));
		InventoryList_[i]->SetPosition({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i)), IMAGE_INVENTORYBAR_POS_DOWN_Y });
	}
}

void Inventory::Update()
{
	// 인벤토리창 On/Off
	ExtendInventoryOn();

	// 키 입력
	ControlSelectBox();

	// 아이콘 업데이트
	IconUpdate();
}

void Inventory::SetPos(float4 _Pos)
{

}

void Inventory::InitKey()
{
	// 키 설정
	if (false == GameEngineInput::GetInst()->IsKey(KEY_INVEN_SELECT_1))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_1, '1');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_2, '2');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_3, '3');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_4, '4');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_5, '5');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_6, '6');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_7, '7');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_8, '8');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_9, '9');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_0, '0');
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_11, VK_OEM_MINUS);
		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_SELECT_12, VK_OEM_PLUS);

		GameEngineInput::GetInst()->CreateKey(KEY_INVEN_EXTEND, 'i');
	}
}

void Inventory::ExtendInventoryOn()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_EXTEND))
	{
		if (false == ExtendFlg)
		{
			ExtendFlg = true;
			RendererSelectBox_->Off();
			RendererInven_->SetImage(IMAGE_INVENTORY_EXTEND);
			RendererInven_->SetPivot({ IMAGE_INVENTORY_EXT_POS_X , IMAGE_INVENTORY_EXT_POS_Y });
		}
		else
		{
			ExtendFlg = false;
			RendererSelectBox_->On();
			RendererInven_->SetImage(IMAGE_INVENTORY_BAR);

			// 인벤토리바 위치
			RendererInven_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });
		}
	}
}

void Inventory::ControlSelectBox()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_1))
	{
		SelectBoxHotkey_ = 0;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_2))
	{
		SelectBoxHotkey_ = 1;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_3))
	{
		SelectBoxHotkey_ = 2;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_4))
	{
		SelectBoxHotkey_ = 3;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_5))
	{
		SelectBoxHotkey_ = 4;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_6))
	{
		SelectBoxHotkey_ = 5;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_7))
	{
		SelectBoxHotkey_ = 6;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_8))
	{
		SelectBoxHotkey_ = 7;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_9))
	{
		SelectBoxHotkey_ = 8;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_0))
	{
		SelectBoxHotkey_ = 9;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_11))
	{
		SelectBoxHotkey_ = 10;
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_12))
	{
		SelectBoxHotkey_ = 11;
	}

	if (false == ExtendFlg)
	{
		RendererSelectBox_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)SelectBoxHotkey_)), IMAGE_INVENTORYBAR_POS_DOWN_Y });
	}
	else
	{
		RendererSelectBox_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)SelectBoxHotkey_)), IMAGE_INVENTORY_EXT_POS_Y - 70 });
	}

}

// 테스트
void Inventory::AddItemToInventory(Item& _item)
{
	Item& item = _item;

	for (size_t i = 0; i < 36; i++)
	{
		if (nullptr == InventoryList_[i])
		{
			InventoryList_[i] = &item;
			

			break;
		}
	}
}

void Inventory::IconUpdate()
{
	for (size_t i = 0; i < 36; i++)
	{
		if (InventoryList_[i] == nullptr)
		{
			continue;
		}
		else
		{
			//InventoryList_[i]->SetIconRenderer(InventoryList_[i]->GetIconRenderer());
			InventoryList_[i]->SetPosition({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i)), IMAGE_INVENTORYBAR_POS_DOWN_Y });
		}
	}
}