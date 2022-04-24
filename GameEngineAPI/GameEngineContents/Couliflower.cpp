#include "Couliflower.h"
#include "ContentsEnums.h"
#include "CouliflowerFruit.h"

Couliflower::Couliflower() 
{
}

Couliflower::~Couliflower() 
{
}

void Couliflower::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 8;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(6);
}

Item* Couliflower::CreateItem()
{
	// 수정예정
	Item* NewItem = this->GetLevel()->CreateActor<CouliflowerFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}