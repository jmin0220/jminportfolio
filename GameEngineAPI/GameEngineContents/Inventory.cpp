#include "Inventory.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineString.h>
#include "ItemTable.h"

char Inventory::SelectBoxHotkey_;
float4 Inventory::Pos_;
bool Inventory::ExtendFlg;
std::string Inventory::SelectedItem_;

Inventory::Inventory() 
	: RendererInven_(nullptr)
	, RendererSelectBox_(nullptr)
{
}

Inventory::~Inventory() 
{
	for (size_t i = 0; i < 36; i++)
	{
		delete InventoryList_[i];
		InventoryList_[i] = nullptr;
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


	if (InventoryList_[0] == nullptr)
	{
		for (size_t i = 0; i < 36; i++)
		{
			// 인벤에 아이템의 정보를 집어넣음.
			// 비어있는 인벤토리 생성
			InventoryList_[i] = new Item;
			InventoryList_[i]->SetIconRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));
			InventoryList_[i]->GetIconRenderer().CameraEffectOff();
			InventoryList_[i]->GetIconRenderer().SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i)), IMAGE_INVENTORYBAR_POS_DOWN_Y - 22 });

			if (i < 12)
			{
				InventoryList_[i]->GetIconRenderer().On();
			}
			else
			{
				InventoryList_[i]->GetIconRenderer().Off();
			}
		}
	}

	SelectItem(0);
}

void Inventory::Update()
{
	// 인벤토리창 On/Off
	ExtendInventoryOn();

	// 키 입력
	ControlSelectBox();
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
		SelectItem(0);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_2))
	{
		SelectItem(1);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_3))
	{
		SelectItem(2);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_4))
	{
		SelectItem(3);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_5))
	{
		SelectItem(4);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_6))
	{
		SelectItem(5);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_7))
	{
		SelectItem(6);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_8))
	{
		SelectItem(7);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_9))
	{
		SelectItem(8);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_0))
	{
		SelectItem(9);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_11))
	{
		SelectItem(10);
	}
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_SELECT_12))
	{
		SelectItem(11);
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

void Inventory::SetPos(float4 _Pos)
{

}

// 테스트
void Inventory::AddItemToInventory(int _ItemNum)
{
	for (size_t i = 0; i < 36; i++)
	{
		// 아이콘은 인벤토리에서 아이템의 위치를 표시
		// 아이콘이 Empty일경우 해당 인벤토리칸은 비어있어야 함.
		if (InventoryList_[i]->GetIconRenderer().GetImage()->GetNameCopy() == GameEngineString::ToUpperReturn(IMAGE_INVENTORY_EMPTY))
		{
			InventoryList_[i]->SetIconRendererImage(_ItemNum);
			InventoryList_[i]->GetIconRenderer().SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i)), IMAGE_INVENTORYBAR_POS_DOWN_Y - 22 });
			
			break;
		}
	}
}