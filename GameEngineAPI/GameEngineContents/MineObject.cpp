#include "MineObject.h"
#include "ContentsEnums.h"
#include "Diamond.h"
#include "Ruby.h"
#include "Jade.h"
#include "Amethyst.h"
#include "Topaz.h"
#include <windows.h>

int MineObject::PrevIndex_ = 0;

MineObject::MineObject() 
{
	RandomItem_ = new GameEngineRandom();
	ItemIndex_ = 0;
}

MineObject::~MineObject() 
{
	delete RandomItem_;
	RandomItem_ = nullptr;
}

void MineObject::Start()
{
	// 생성될때 무작위 광석이 생성됨
	Renderer_ = CreateRenderer(IMAGE_ITEM_MINES, (int)ORDER::FRONTA);

	for (;;)
	{
		if (PrevIndex_ == ItemIndex_)
		{
			ItemIndex_ = RandomItem_->RandomInt(0, 4);
		}
		else
		{
			PrevIndex_ = ItemIndex_;
			break;
		}
	}

	Renderer_->SetIndex(ItemIndex_);
	SetHp(3);
}

Item* MineObject::CreateItem()
{
	Item* NewItem = nullptr;

	// 생성됐던 Index에 따라서 알맞는 아이템을 생성함
	switch (ItemIndex_)
	{
	case 0:
		NewItem = this->GetLevel()->CreateActor<Diamond>();
		break;
	case 1:
		NewItem = this->GetLevel()->CreateActor<Ruby>();
		break;
	case 2:
		NewItem = this->GetLevel()->CreateActor<Jade>();
		break;
	case 3:
		NewItem = this->GetLevel()->CreateActor<Amethyst>();
		break;
	case 4:
		NewItem = this->GetLevel()->CreateActor<Topaz>();
		break;
	}

	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}

void MineObject::Update()
{
	UpdateVibrate();
}