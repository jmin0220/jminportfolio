#include "Starfruit.h"
#include "ContentsEnums.h"
#include "StarfruitFruit.h"

Starfruit::Starfruit() 
{
}

Starfruit::~Starfruit() 
{
}

void Starfruit::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 56;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(7);
}

Item* Starfruit::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<StarfruitFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}