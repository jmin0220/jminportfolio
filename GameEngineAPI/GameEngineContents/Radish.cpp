#include "Radish.h"
#include "ContentsEnums.h"
#include "RadishFruit.h"

Radish::Radish() 
{
}

Radish::~Radish() 
{
}

void Radish::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 48;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(5);
}

Item* Radish::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<RadishFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}