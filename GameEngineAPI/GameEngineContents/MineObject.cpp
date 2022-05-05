#include "MineObject.h"
#include "ContentsEnums.h"
#include "Diamond.h"
#include "Ruby.h"
#include "Jade.h"
#include "Amethyst.h"
#include "Topaz.h"

MineObject::MineObject() 
{
	RandomItem_ = new GameEngineRandom();
}

MineObject::~MineObject() 
{
	delete RandomItem_;
	RandomItem_ = nullptr;
}

void MineObject::Start()
{
	Renderer_ = CreateRenderer(IMAGE_ITEM_MINES, (int)ORDER::FRONTA);
	ItemIndex_ = RandomItem_->RandomInt(0, 4);
}

Item* MineObject::CreateItem()
{
	Item* NewItem = nullptr;

	switch (ItemIndex_)
	{
	case 0:
		this->GetLevel()->CreateActor<Diamond>();
		break;
	case 1:
		this->GetLevel()->CreateActor<Ruby>();
		break;
	case 2:
		this->GetLevel()->CreateActor<Jade>();
		break;
	case 3:
		this->GetLevel()->CreateActor<Amethyst>();
		break;
	case 4:
		this->GetLevel()->CreateActor<Topaz>();
		break;
	}

	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}