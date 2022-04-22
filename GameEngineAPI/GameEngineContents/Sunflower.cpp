#include "Sunflower.h"
#include "ContentsEnums.h"
#include "ParsnipFruit.h"

Sunflower::Sunflower() 
{
}

Sunflower::~Sunflower() 
{
}

void Sunflower::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 96;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(5);
}

Item* Sunflower::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<ParsnipFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}