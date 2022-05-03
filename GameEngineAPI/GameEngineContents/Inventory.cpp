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
std::string Inventory::SelectedItemName_;
int Inventory::SelectedItemNumber_;
Item* Inventory::InventorySaver_[36];

Inventory::Inventory() 
	: RendererInven_(nullptr)
	, RendererSelectBox_(nullptr)
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
	

	if (InventoryList_[0] == nullptr)
	{
		for (size_t i = 0; i < 36; i++)
		{
			// �κ��� �������� ������ �������.
			// ����ִ� �κ��丮 ����
			InventoryList_[i] = this->GetLevel()->CreateActor<Item>();
			InventoryList_[i]->SetIconRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));
			InventoryList_[i]->SetItemRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::PLAYER));
			InventoryList_[i]->GetIconRenderer().CameraEffectOff();
			InventoryList_[i]->GetIconRenderer().SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i)), IMAGE_INVENTORYBAR_POS_DOWN_Y - 22 });
			InventoryList_[i]->SetItemName(ITEM_NAME_EMPTY);
			InventoryList_[i]->Counter_ = "0";

			// Font ����
			InventoryList_[i]->Font_[0] = this->GetLevel()->CreateActor<Font>((int)ORDER::UIFONT);
			InventoryList_[i]->Font_[1] = this->GetLevel()->CreateActor<Font>((int)ORDER::UIFONT);

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

	SwapItem_ = this->GetLevel()->CreateActor<Item>();
	SwapItem_->SetItemRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));
	SwapItem_->SetIconRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));

	InitKey();
	CollisionInit();


}
void Inventory::Update()
{
	// �κ��丮â On/Off
	ExtendInventoryOn();

	// Ű �Է�
	ControlSelectBox();

	// ������ ������
	ItemPosCalc();
}

void Inventory::InventoryInit()
{
	if (InventoryList_[0]->GetItemName() != ITEM_NAME_EMPTY)
	{
		// TODO::���װ� ����� ��ġ?
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

// ������ ����
void Inventory::SelectItem(int i)
{
	if (false == ExtendFlg_)
	{
		SelectBoxHotkey_ = i;
		SelectedItemName_ = InventoryList_[i]->GetItemName();
		SelectedItemNumber_ = i;
	}

	GameEngineSound::SoundPlayOneShot(SOUND_SMALLSELCET);
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

			// �ø��� ����
			for (size_t i = 0; i < 12; i++)
			{
				ColInventoryNormalBox_[i]->On();
			}
			for (size_t i = 0; i < 36; i++)
			{
				ColInventoryExtendBox_[i]->Off();
			}
		}
		else
		{
			ExtendFlg_ = false;
			RendererInven_->SetImage(IMAGE_INVENTORY_BAR);

			// �κ��丮�� ��ġ
			RendererInven_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });

			// �ø��� ����
			for (size_t i = 0; i < 12; i++)
			{
				ColInventoryNormalBox_[i]->Off();
			}
			for (size_t i = 0; i < 36; i++)
			{
				ColInventoryExtendBox_[i]->On();
			}
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
			if (false == InventoryList_[i]->ClickedFlg)
			{
				PosX = IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i));
				PosY = IMAGE_INVENTORYBAR_POS_DOWN_Y + 6;

				InventoryList_[i]->GetIconRenderer().SetPivot({ PosX, PosY });
				InventoryList_[i]->SetItemNum();
			}
			else
			{
				continue;
			}
		}

		for (size_t i = 12; i < 36; i++)
		{
			if (false == InventoryList_[i]->ClickedFlg)
			{
				InventoryList_[i]->GetIconRenderer().Off();
				InventoryList_[i]->Font_[0]->GetRendererFont()->Off();
				InventoryList_[i]->Font_[1]->GetRendererFont()->Off();
			}
		}
	}
	else
	{
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 12; j++)
			{
				if (false == InventoryList_[j + (12 * i)]->ClickedFlg)
				{
					PosX = IMAGE_INVENTORY_EXT_POS_X - (352 - (64 * (float)j));
					PosY = IMAGE_INVENTORY_EXT_POS_Y - (58 - (64 * (float)i));

					InventoryList_[j + (12 * i)]->GetIconRenderer().SetPivot({ PosX, PosY });
					InventoryList_[j + (12 * i)]->SetItemNum();
					InventoryList_[j + (12 * i)]->GetIconRenderer().On();
				}
				else
				{
					continue;
				}
			}
		}
	}
}

// �κ��丮�� ������ �߰�
int Inventory::AddItemToInventory(int _ItemNum)
{
	int InsertSuccessFlg = 0;

	// �������� �κ��丮���� �������� ��ġ�� ǥ��
	// �������� Empty�ϰ�� �ش� �κ��丮ĭ�� ����־�� ��.
	// ������ �� �ְų�, ����ְų�.
	for (size_t i = 0; i < 36; i++)
	{
		// �̹� ���� �̸��� �������� �����Ұ�� 
		if ((StringtoItemTable(InventoryList_[i]->GetItemName()) == _ItemNum
			&& InventoryList_[i]->Countable == true))
		{
			InventoryList_[i]->SetIconRendererInfo(_ItemNum);
			InventoryList_[i]->AddCounter();
			InventoryList_[i]->SetItemNum();

			InsertSuccessFlg = 1;
			return InsertSuccessFlg;
		}
	}

	for (size_t i = 0; i < 36; i++)
	{
		// ���� �̸��� �������� �������� ������� ����� ����ִ´�
		if (InventoryList_[i]->GetIconRenderer().GetImage()->GetNameCopy() == GameEngineString::ToUpperReturn(IMAGE_INVENTORY_EMPTY))
		{
			InventoryList_[i]->SetIconRendererInfo(_ItemNum);
			InventoryList_[i]->AddCounter();
			InventoryList_[i]->SetItemNum();

			InsertSuccessFlg = 1;
			return InsertSuccessFlg;
		}
	}

	// �־����� 1
	// ���־����� 0
	return InsertSuccessFlg;
}

// �κ��丮���� ������ ����
void Inventory::DeleteItem(int i)
{
	InventoryList_[i]->GetIconRenderer().SetImage(IMAGE_INVENTORY_EMPTY);
	InventoryList_[i]->GetItemRenderer().SetImage(IMAGE_INVENTORY_EMPTY);
	InventoryList_[i]->SetItemName(ITEM_NAME_EMPTY);
	InventoryList_[i]->Font_[0]->GetRendererFont()->Off();
	InventoryList_[i]->Font_[1]->GetRendererFont()->Off();
	InventoryList_[i]->Countable = false;
	InventoryList_[i]->Counter_ = "0";

	// ������ ĭ�� �ٽ� ���������μ� ���� ������ �ʱ�ȭ
	SelectItem(i);
}


// ������ �̵�
void Inventory::SwapItem(int _Origin, int _Target)
{
	SwapItem_->GetItemRenderer().SetImage(InventoryList_[_Target]->GetItemRenderer().GetImage()->GetNameCopy());
	SwapItem_->GetIconRenderer().SetImage(InventoryList_[_Target]->GetIconRenderer().GetImage()->GetNameCopy());
	SwapItem_->SetItemName(InventoryList_[_Target]->GetItemName());
	SwapItem_->SetIndexNum(InventoryList_[_Target]->GetIndexNum());
	SwapItem_->Counter_ = InventoryList_[_Target]->Counter_;
	SwapItem_->Countable = InventoryList_[_Target]->Countable;

	InventoryList_[_Target]->GetItemRenderer().SetImage(InventoryList_[_Origin]->GetItemRenderer().GetImage()->GetNameCopy());
	InventoryList_[_Target]->GetIconRenderer().SetImage(InventoryList_[_Origin]->GetIconRenderer().GetImage()->GetNameCopy());
	InventoryList_[_Target]->SetItemName(InventoryList_[_Origin]->GetItemName());
	InventoryList_[_Target]->SetIndexNum(InventoryList_[_Origin]->GetIndexNum());
	InventoryList_[_Target]->GetIconRenderer().SetIndex(InventoryList_[_Origin]->GetIndexNum());
	InventoryList_[_Target]->Counter_ = InventoryList_[_Origin]->Counter_;
	InventoryList_[_Target]->Countable = InventoryList_[_Origin]->Countable;

	InventoryList_[_Origin]->GetItemRenderer().SetImage(SwapItem_->GetItemRenderer().GetImage()->GetNameCopy());
	InventoryList_[_Origin]->GetIconRenderer().SetImage(SwapItem_->GetIconRenderer().GetImage()->GetNameCopy());
	InventoryList_[_Origin]->SetItemName(SwapItem_->GetItemName());
	InventoryList_[_Origin]->SetIndexNum(SwapItem_->GetIndexNum());
	InventoryList_[_Origin]->GetIconRenderer().SetIndex(SwapItem_->GetIndexNum());
	InventoryList_[_Origin]->Counter_ = SwapItem_->Counter_;
	InventoryList_[_Origin]->Countable = SwapItem_->Countable;

	// ��ȯ�Ѱ͵��� ��Ʈ�� ����
	// ���� ��Ʈ �������� SetItemNum���� �ٽ� ������
	InventoryList_[_Origin]->Font_[0]->GetRendererFont()->Off();
	InventoryList_[_Origin]->Font_[1]->GetRendererFont()->Off();
	InventoryList_[_Target]->Font_[0]->GetRendererFont()->Off();
	InventoryList_[_Target]->Font_[1]->GetRendererFont()->Off();
}

// �ø���
void Inventory::CollisionInit()
{
	float PosX = 0.0f;
	float PosY = 0.0f;

	ColInventoryBar_ = CreateCollision(COL_GROUP_INVENTORY_BAR, { 800, 96 }, { IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });
	ColInventoryExtBar_ = CreateCollision(COL_GROUP_INVENTORY_EXTEND_BAR, { 848, 272 }, { IMAGE_INVENTORY_EXT_POS_X, IMAGE_INVENTORY_EXT_POS_Y });
	ColInventoryExtBar_->Off();

	for (size_t i = 0; i < 12; i++)
	{
		PosX = IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i));
		PosY = IMAGE_INVENTORYBAR_POS_DOWN_Y;

		ColInventoryNormalBox_[i] = CreateCollision(COL_GROUP_INVENTORY_BOX, {64, 64}, { PosX, PosY });
	}

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			PosX = IMAGE_INVENTORY_EXT_POS_X - (352 - (64 * (float)j));
			PosY = IMAGE_INVENTORY_EXT_POS_Y - (58 - (64 * (float)i));

			ColInventoryExtendBox_[j + (12 * i)] = CreateCollision(COL_GROUP_INVENTORY_EXTEND_BOX, {64, 64}, {PosX, PosY});
			ColInventoryExtendBox_[j + (12 * i)]->Off();
		}
	}
}

// ���� ��ȯ
void Inventory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	InventoryDownload();
}

void Inventory::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	InventoryUpload();
}

void Inventory::InventoryUpload()
{
	// ������ �Ѱ��ֱ�
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

		// ����
		InventorySaver_[i]->Countable = InventoryList_[i]->Countable;
		InventorySaver_[i]->Counter_ = InventoryList_[i]->Counter_;
	}
}


void Inventory::InventoryDownload()
{
	// ������ ��������
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

		// ����
		InventoryList_[i]->Countable = InventorySaver_[i]->Countable;
		InventoryList_[i]->Counter_ = InventorySaver_[i]->Counter_;

		// �̹����� ������� ���� ��쿡�� �ε��� ���� �ϱ�
		if (InventoryList_[i]->GetItemName() != ITEM_NAME_EMPTY)
		{
			InventoryList_[i]->GetIconRenderer().SetIndex(InventorySaver_[i]->GetIndexNum());
		}
	}
}

void Inventory::FontDeath()
{
	for (int i = 0; i < 36; i++)
	{
		InventoryList_[i]->Font_[0]->Death();
		InventoryList_[i]->Font_[1]->Death();
	}
}