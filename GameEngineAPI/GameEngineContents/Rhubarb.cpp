#include "Rhubarb.h"
#include "ContentsEnums.h"
#include "ParsnipFruit.h"

Rhubarb::Rhubarb() 
{
}

Rhubarb::~Rhubarb() 
{
}

void Rhubarb::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 24;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(6);
}

Item* Rhubarb::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<ParsnipFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}
