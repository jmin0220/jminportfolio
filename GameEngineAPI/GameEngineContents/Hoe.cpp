#include "Hoe.h"
#include "Inventory.h"

Hoe::Hoe() 
{
	ItemName_ = ITEM_NAME_HOE;
}

Hoe::~Hoe() 
{
}

void Hoe::Start()
{
	ItemRenderer_ = CreateRenderer(IMAGE_TOOL_SET1);
	ItemRenderer_->SetIndex(0);

	IconRenderer_ = CreateRenderer(IMAGE_TOOL_SET1);
	IconRenderer_->SetIndex(5);
	IconRenderer_->CameraEffectOff();
}

void Hoe::Update()
{
}