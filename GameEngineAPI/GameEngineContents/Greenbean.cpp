#include "Greenbean.h"
#include "ContentsEnums.h"
#include "GreenbeanFruit.h"

Greenbean::Greenbean() 
{
}

Greenbean::~Greenbean() 
{
}

void Greenbean::Start()
{
	Hp_ = 1;
	RenderCropsIndex_ = 104;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(RenderCropsIndex_);
	SetGrowLevel(0);
	SetMaxLevel(7);
}

Item* Greenbean::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<GreenbeanFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}