#include "Eggplant.h"
#include "ContentsEnums.h"
#include "EggplantFruit.h"

Eggplant::Eggplant() 
{
}

Eggplant::~Eggplant() 
{
}

void Eggplant::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 64;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(7);
}

Item* Eggplant::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<EggplantFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}