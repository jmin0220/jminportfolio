#include "Parsnip.h"
#include "ContentsEnums.h"

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

void Parsnip::CreateItem()
{
	int ItemNum = RandomItem_->RandomInt(1, 4);

	for (size_t i = 0; i < ItemNum; i++)
	{
		GameEngineActor* NewItem = this->GetLevel()->CreateActor<Parsnip>();
		float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
		float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

		NewItem->SetPosition({ PosX, PosY });

	}
}