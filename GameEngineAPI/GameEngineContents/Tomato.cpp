#include "Tomato.h"
#include "ContentsEnums.h"
#include "ParsnipFruit.h"

Tomato::Tomato() 
{
}

Tomato::~Tomato() 
{
}

void Tomato::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 32;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(7);
}

Item* Tomato::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<ParsnipFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}