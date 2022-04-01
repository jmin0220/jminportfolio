#include "Inventory.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

// �׽�Ʈ��
#include "HoeBasic.h"

Inventory::Inventory() 
	: RendererInven_(nullptr)
	, RendererSelectBox_(nullptr)
	, SelectBoxHotkey_(0)
	, ExtendFlg(false)
{
}

Inventory::~Inventory() 
{
}

void Inventory::Start()
{
	// InventoryBar�������̽�������
	// ���͸� �߾ӿ� ��ġ
	SetPosition({0, 0});

	RendererInven_ = CreateRenderer(IMAGE_INVENTORY_BAR);
	RendererSelectBox_ = CreateRenderer(IMAGE_INVENTORY_SELECT);
	
	// ������ �׸��� �������Ǵ� ��
	// RendererBar_->SetPivot({ IMAGE_INVENTORYBAR_POS_UP_X, IMAGE_INVENTORYBAR_POS_UP_Y });
	RendererInven_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });
	RendererSelectBox_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)SelectBoxHotkey_)), IMAGE_INVENTORYBAR_POS_DOWN_Y});

	RendererInven_->CameraEffectOff();
	RendererSelectBox_->CameraEffectOff();

	// Ű ����
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

void Inventory::Update()
{
	// �κ��丮â On/Off
	ExtendInventoryOn();

	// Ű �Է�
	ControlSelectBox();

}

void Inventory::SetPos(float4 _Pos)
{

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

			// �κ��丮�� ��ġ
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

// �׽�Ʈ
void Inventory::AddItemToInventory(Item* _item)
{
	Item* item = _item;

	for (size_t i = 0; i < 36 ; i++)
	{
		if (nullptr == InventoryList_[i])
		{
			InventoryList_[i] = item;
		}
	}
}