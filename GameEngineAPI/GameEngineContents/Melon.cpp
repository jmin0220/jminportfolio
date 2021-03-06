#include "Melon.h"
#include "ContentsEnums.h"
#include "MelonFruit.h"

Melon::Melon() 
{
}

Melon::~Melon() 
{
}

void Melon::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 128;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(6);
}

Item* Melon::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<MelonFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}