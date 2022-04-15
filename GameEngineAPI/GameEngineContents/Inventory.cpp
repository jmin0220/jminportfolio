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
bool Inventory::ExtendFlg_;
std::string Inventory::SelectedItem_;
Item* Inventory::InventorySaver_[36];

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
	

	if (InventoryList_[0] == nullptr)
	{
		for (size_t i = 0; i < 36; i++)
		{
			// �κ��� �������� ������ �������.
			// ����ִ� �κ��丮 ����
			InventoryList_[i] = new Item;
			InventoryList_[i]->SetIconRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));
			InventoryList_[i]->SetItemRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::PLAYER));
			InventoryList_[i]->GetIconRenderer().CameraEffectOff();
			InventoryList_[i]->GetIconRenderer().SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i)), IMAGE_INVENTORYBAR_POS_DOWN_Y - 22 });
			InventoryList_[i]->SetItemName(ITEM_NAME_EMPTY);

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

	InitKey();
	CollisionInit();
}

void Inventory::Update()
{
	// �κ��丮â On/Off
	ExtendInventoryOn();

	// Ű �Է�
	ControlSelectBox();
}

void Inventory::InventoryInit()
{
	if (InventoryList_[0]->GetItemName() != ITEM_NAME_EMPTY)
	{
		memcpy(InventorySaver_, InventoryList_, sizeof(InventoryList_));
	}

	SelectItem(0);
}

// Ű �ʱ�ȭ
void Inventory::InitKey()
{
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

void Inventory::SelectItem(int i)
{
	if (false == ExtendFlg_)
	{
		SelectBoxHotkey_ = i;
		SelectedItem_ = InventoryList_[i]->GetItemName();
	}
}

// �κ��丮 Ȯ��
void Inventory::ExtendInventoryOn()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_EXTEND))
	{
		if (false == ExtendFlg_)
		{
			ExtendFlg_ = true;
			RendererInven_->SetImage(IMAGE_INVENTORY_EXTEND);

			// �κ��丮�� ��ġ
			RendererInven_->SetPivot({ IMAGE_INVENTORY_EXT_POS_X , IMAGE_INVENTORY_EXT_POS_Y });
		}
		else
		{
			ExtendFlg_ = false;
			RendererInven_->SetImage(IMAGE_INVENTORY_BAR);

			// �κ��丮�� ��ġ
			RendererInven_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });
		}

		ItemPosCalc();
	}
}

// Ű�Է�
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

	if (false == ExtendFlg_)
	{
		RendererSelectBox_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)SelectBoxHotkey_)), IMAGE_INVENTORYBAR_POS_DOWN_Y });
	}
	else
	{
		RendererSelectBox_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)SelectBoxHotkey_)), IMAGE_INVENTORY_EXT_POS_Y - 65 });
	}

}

// ������ ������
void Inventory::ItemPosCalc()
{
	float PosX = 0.0f;
	float PosY = 0.0f;

	if (false == ExtendFlg_)
	{
		for (size_t i = 0; i < 12; i++)
		{
			PosX = IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i));
			PosY = IMAGE_INVENTORYBAR_POS_DOWN_Y - 18;

			InventoryList_[i]->GetIconRenderer().SetPivot({ PosX, PosY });
		}

		for (size_t i = 12; i < 36; i++)
		{
			InventoryList_[i]->GetIconRenderer().Off();
		}

	}
	else
	{
		for (size_t i = 0; i < 12; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				PosX = IMAGE_INVENTORY_EXT_POS_X - (352 - (64 * (float)i));
				PosY = IMAGE_INVENTORY_EXT_POS_Y - (83 - (64 * (float)j)) + 4 * j;

				InventoryList_[i + (12 * j)]->GetIconRenderer().SetPivot({ PosX, PosY });
				InventoryList_[i + (12 * j)]->GetIconRenderer().On();
			}
		}
	}
}

// �κ��丮�� ������ �߰�
int Inventory::AddItemToInventory(int _ItemNum)
{
	int InsertSuccessFlg = 0;

	for (size_t i = 0; i < 36; i++)
	{
		// �������� �κ��丮���� �������� ��ġ�� ǥ��
		// �������� Empty�ϰ�� �ش� �κ��丮ĭ�� ����־�� ��.
		if (InventoryList_[i]->GetIconRenderer().GetImage()->GetNameCopy() == GameEngineString::ToUpperReturn(IMAGE_INVENTORY_EMPTY))
		{
			InventoryList_[i]->SetIconRendererInfo(_ItemNum);

			InsertSuccessFlg = 1;
			break;
		}
	}

	ItemPosCalc();

	// �־����� 1
	// ���־����� 0
	return InsertSuccessFlg;
}

// �ø���
void Inventory::CollisionInit()
{
	float PosX = 0.0f;
	float PosY = 0.0f;

	ColInventoryBar_ = CreateCollision(COL_GROUP_INVENTORY_BAR, { 800, 96 }, { IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });
	ColInventoryExtBar_ = CreateCollision(COL_GROUP_INVENTORY_EXTEND_BAR, { 848, 272 }, { IMAGE_INVENTORY_EXT_POS_X, IMAGE_INVENTORY_EXT_POS_Y });

	for (size_t i = 0; i < 12; i++)
	{
		PosX = IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i));
		PosY = IMAGE_INVENTORYBAR_POS_DOWN_Y;

		ColInventoryNormalBox_[i] = CreateCollision(COL_GROUP_INVENTORY_BOX, {64, 64}, { PosX, PosY });
	}

	for (size_t i = 0; i < 12; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			PosX = IMAGE_INVENTORY_EXT_POS_X - (352 - (64 * (float)i));
			PosY = IMAGE_INVENTORY_EXT_POS_Y - (83 - (64 * (float)j)) + 4 * j;

			ColInventoryExtendBox_[i] = CreateCollision(COL_GROUP_INVENTORY_EXTEND_BOX, {64, 64}, {PosX, PosY});
		}
	}
}

// ���� ��ȯ
void Inventory::LevelChangeStart()
{
	// ���� ������ ������ ��������
	for (size_t i = 0; i < 36; i++)
	{
		// ������ �������� �̹����� ����
		InventoryList_[i]->GetItemRenderer().SetImage(InventorySaver_[i]->GetItemRenderer().GetImage()->GetNameCopy());
		// ������ �������� �̹����� ����
		InventoryList_[i]->GetIconRenderer().SetImage(InventorySaver_[i]->GetIconRenderer().GetImage()->GetNameCopy());
		// �ش� �κ��丮�� ����ִ� ������ �̸��� ����
		InventoryList_[i]->SetItemName(InventorySaver_[i]->GetItemName());
		// �̹��� �ε��� ���� �� ����
		InventoryList_[i]->SetIndexNum(InventorySaver_[i]->GetIndexNum());

		// �̹����� ������� ���� ��쿡�� �ε��� ���� �ϱ�
		if (InventoryList_[i]->GetItemName() != ITEM_NAME_EMPTY)
		{
			InventoryList_[i]->GetIconRenderer().SetIndex(InventorySaver_[i]->GetIndexNum());
		}
	}
}

void Inventory::LevelChangeEnd()
{
	// ���� ������ ������ �Ѱ��ֱ�
	for (size_t i = 0; i < 36; i++)
	{
		// ������ �������� �̹����� ����
		InventorySaver_[i]->GetItemRenderer().SetImage(InventoryList_[i]->GetItemRenderer().GetImage()->GetNameCopy());
		// ������ �������� �̹����� ����
		InventorySaver_[i]->GetIconRenderer().SetImage(InventoryList_[i]->GetIconRenderer().GetImage()->GetNameCopy());
		// �ش� �κ��丮�� ����ִ� ������ �̸��� ����
		InventorySaver_[i]->SetItemName(InventoryList_[i]->GetItemName());
		// �̹��� �ε��� ����
		InventorySaver_[i]->SetIndexNum(InventoryList_[i]->GetIndexNum());
	}
}