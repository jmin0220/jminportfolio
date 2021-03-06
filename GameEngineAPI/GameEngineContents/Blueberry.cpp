#include "Blueberry.h"
#include "ContentsEnums.h"
#include "BlueberryFruit.h"

Blueberry::Blueberry() 
{
}

Blueberry::~Blueberry() 
{
}

void Blueberry::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 136;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(7);
}

Item* Blueberry::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<BlueberryFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}