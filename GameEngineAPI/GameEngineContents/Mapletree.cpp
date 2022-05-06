#include "Mapletree.h"
#include "ContentsEnums.h"
#include "MiniTree.h"

Mapletree::Mapletree() 
{
}

Mapletree::~Mapletree() 
{
}


void Mapletree::Start()
{
	Hp_ = 7;
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_MAPLETREE, (int)ORDER::FRONTA);
	Renderer_->SetIndex(0);
	SetGrowLevel(0);
	SetMaxLevel(4);
}

Item* Mapletree::CreateItem()
{
	Item* NewItem = this->GetLevel()->CreateActor<MiniTree>();
	float PosX = RandomItem_->RandomFloat(GetPosition().x - 30.0f, GetPosition().x + 30.0f);
	float PosY = RandomItem_->RandomFloat(GetPosition().y - 30.0f, GetPosition().y + 30.0f);

	NewItem->SetPosition({ PosX, PosY });

	return NewItem;
}

void Mapletree::Update()
{
	UpdateVibrate();
}