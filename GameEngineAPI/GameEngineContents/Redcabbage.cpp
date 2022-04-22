#include "Redcabbage.h"
#include "ContentsEnums.h"
#include "ParsnipFruit.h"

Redcabbage::Redcabbage() 
{
}

Redcabbage::~Redcabbage() 
{
}

void Redcabbage::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 144;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(6);
}

Item* Redcabbage::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<ParsnipFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}