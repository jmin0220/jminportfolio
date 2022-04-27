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
	for (size_t i = 0; i < 36; i++)
	{
		delete InventoryList_[i];
		InventoryList_[i] = nullptr;
	}

	if (nullptr != SwapItem_)
	{
		delete SwapItem_;
		SwapItem_ = nullptr;
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
	

	if (InventoryList_[0] == nullptr)
	{
		for (size_t i = 0; i < 36; i++)
		{
			// 인벤에 아이템의 정보를 집어넣음.
			// 비어있는 인벤토리 생성
			InventoryList_[i] = new Item;
			InventoryList_[i]->SetIconRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));
			InventoryList_[i]->SetItemRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::PLAYER));
			InventoryList_[i]->GetIconRenderer().CameraEffectOff();
			InventoryList_[i]->GetIconRenderer().SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X - (352 - (64 * (float)i)), IMAGE_INVENTORYBAR_POS_DOWN_Y - 22 });
			InventoryList_[i]->SetItemName(ITEM_NAME_EMPTY);
			InventoryList_[i]->Counter_ = "0";

			// Font 생성
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

	SwapItem_ = new Item;
	SwapItem_->SetItemRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));
	SwapItem_->SetIconRenderer(*CreateRenderer(IMAGE_INVENTORY_EMPTY, (int)ORDER::UIICONS));

	InitKey();
	CollisionInit();


}
void Inventory::Update()
{
	// 인벤토리창 On/Off
	ExtendInventoryOn();

	// 키 입력
	ControlSelectBox();

	// 아이템 렌더링
	ItemPosCalc();
}

void Inventory::InventoryInit()
{
	if (InventoryList_[0]->GetItemName() != ITEM_NAME_EMPTY)
	{
		// TODO::버그가 생기는 위치?
		memcpy(InventorySaver_, InventoryList_, sizeof(InventoryList_));
	}

	SelectItem(0);
}

// 키 초기화
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

// 아이템 선택
void Inventory::SelectItem(int i)
{
	if (false == ExtendFlg_)
	{
		SelectBoxHotkey_ = i;
		SelectedItemName_ = InventoryList_[i]->GetItemName();
		SelectedItemNumber_ = i;
	}
}

// 인벤토리 확장
void Inventory::ExtendInventoryOn()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INVEN_EXTEND))
	{
		if (false == ExtendFlg_)
		{
			ExtendFlg_ = true;
			RendererInven_->SetImage(IMAGE_INVENTORY_EXTEND);

			// 인벤토리바 위치
			RendererInven_->SetPivot({ IMAGE_INVENTORY_EXT_POS_X , IMAGE_INVENTORY_EXT_POS_Y });

			// 컬리전 조정
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

			// 인벤토리바 위치
			RendererInven_->SetPivot({ IMAGE_INVENTORYBAR_POS_DOWN_X, IMAGE_INVENTORYBAR_POS_DOWN_Y });

			// 컬리전 조정
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

// 키입력
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

// 아이템 렌더링
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

// 인벤토리에 아이템 추가
int Inventory::AddItemToInventory(int _ItemNum)
{
	int InsertSuccessFlg = 0;

	// 아이콘은 인벤토리에서 아이템의 위치를 표시
	// 아이콘이 Empty일경우 해당 인벤토리칸은 비어있어야 함.
	// 겹쳐질 수 있거나, 비어있거나.
	for (size_t i = 0; i < 36; i++)
	{
		// 이미 같은 이름의 아이템이 존재할경우 
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
		// 같은 이름의 아이템이 존재하지 않을경우 빈곳에 집어넣는다
		if (InventoryList_[i]->GetIconRenderer().GetImage()->GetNameCopy() == GameEngineString::ToUpperReturn(IMAGE_INVENTORY_EMPTY))
		{
			InventoryList_[i]->SetIconRendererInfo(_ItemNum);
			InventoryList_[i]->AddCounter();
			InventoryList_[i]->SetItemNum();

			InsertSuccessFlg = 1;
			return InsertSuccessFlg;
		}
	}

	// 넣었으면 1
	// 못넣었으면 0
	return InsertSuccessFlg;
}

// 인벤토리에서 아이템 삭제
void Inventory::DeleteItem(int i)
{
	InventoryList_[i]->GetIconRenderer().SetImage(IMAGE_INVENTORY_EMPTY);
	InventoryList_[i]->GetItemRenderer().SetImage(IMAGE_INVENTORY_EMPTY);
	InventoryList_[i]->SetItemName(ITEM_NAME_EMPTY);
	InventoryList_[i]->Font_[0]->GetRendererFont()->Off();
	InventoryList_[i]->Font_[1]->GetRendererFont()->Off();
	InventoryList_[i]->Countable = false;
	InventoryList_[i]->Counter_ = "0";
}


// 아이템 이동
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

	// 교환한것들의 폰트를 끄기
	// 꺼진 폰트 렌더러는 SetItemNum에서 다시 켜질것
	InventoryList_[_Origin]->Font_[0]->GetRendererFont()->Off();
	InventoryList_[_Origin]->Font_[1]->GetRendererFont()->Off();
	InventoryList_[_Target]->Font_[0]->GetRendererFont()->Off();
	InventoryList_[_Target]->Font_[1]->GetRendererFont()->Off();
}

// 컬리전
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

// 레벨 전환
void Inventory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	// 이전 레벨의 정보를 가져오기
	for (size_t i = 0; i < 36; i++)
	{
		// 아이템 렌더러의 이미지를 복사
		InventoryList_[i]->GetItemRenderer().SetImage(InventorySaver_[i]->GetItemRenderer().GetImage()->GetNameCopy());
		// 아이콘 렌더러의 이미지를 복사
		InventoryList_[i]->GetIconRenderer().SetImage(InventorySaver_[i]->GetIconRenderer().GetImage()->GetNameCopy());
		// 해당 인벤토리에 들어있는 아이템 이름을 복사
		InventoryList_[i]->SetItemName(InventorySaver_[i]->GetItemName());
		// 이미지 인덱스 복사 및 설정
		InventoryList_[i]->SetIndexNum(InventorySaver_[i]->GetIndexNum());

		// 수량
		InventoryList_[i]->Countable = InventorySaver_[i]->Countable;
		InventoryList_[i]->Counter_ = InventorySaver_[i]->Counter_;

		// 이미지가 비어있지 않을 경우에만 인덱스 설정 하기
		if (InventoryList_[i]->GetItemName() != ITEM_NAME_EMPTY)
		{
			InventoryList_[i]->GetIconRenderer().SetIndex(InventorySaver_[i]->GetIndexNum());
		}
	}
}

void Inventory::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	// 다음 레벨에 정보를 넘겨주기
	for (size_t i = 0; i < 36; i++)
	{
		// 아이템 렌더러의 이미지를 복사
		InventorySaver_[i]->GetItemRenderer().SetImage(InventoryList_[i]->GetItemRenderer().GetImage()->GetNameCopy());
		// 아이콘 렌더러의 이미지를 복사
		InventorySaver_[i]->GetIconRenderer().SetImage(InventoryList_[i]->GetIconRenderer().GetImage()->GetNameCopy());
		// 해당 인벤토리에 들어있는 아이템 이름을 복사
		InventorySaver_[i]->SetItemName(InventoryList_[i]->GetItemName());
		// 이미지 인덱스 복사
		InventorySaver_[i]->SetIndexNum(InventoryList_[i]->GetIndexNum());

		// 수량
		InventorySaver_[i]->Countable = InventoryList_[i]->Countable;
		InventorySaver_[i]->Counter_ = InventoryList_[i]->Counter_;
	}
}