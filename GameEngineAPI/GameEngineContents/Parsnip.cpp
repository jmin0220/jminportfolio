#include "Parsnip.h"
#include "ContentsEnums.h"
#include "ParsnipFruit.h"

Parsnip::Parsnip()
{
}

Parsnip::~Parsnip() 
{
}

void Parsnip::Start()
{
	Hp_ = 1;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(0);
}

Item* Parsnip::CreateItem()
{
	// 수정예정
	Item* NewItem = this->GetLevel()->CreateActor<ParsnipFruit>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}