#include "Garlic.h"
#include "ContentsEnums.h"
#include "GarlicFruit.h"

Garlic::Garlic() 
{
}

Garlic::~Garlic() 
{
}

void Garlic::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 16;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(5);
}

Item* Garlic::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<GarlicFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}