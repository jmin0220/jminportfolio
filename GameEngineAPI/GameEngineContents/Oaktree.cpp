#include "Oaktree.h"
#include "ContentsEnums.h"
#include "MiniTree.h"

Oaktree::Oaktree() 
{
}

Oaktree::~Oaktree() 
{
}


void Oaktree::Start()
{
	Hp_ = 7;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_OAKTREE, (int)ORDER::FRONTA);
	Renderer_->SetIndex(0);
}

Item* Oaktree::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<MiniTree>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}