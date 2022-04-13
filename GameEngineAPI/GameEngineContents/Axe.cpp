#include "Axe.h"

Axe::Axe() 
{
	ItemName_ = ITEM_NAME_AXE;
}

Axe::~Axe() 
{
}

void Axe::Start()
{
	ItemRenderer_ = CreateRenderer(IMAGE_TOOL_SET1);
	ItemRenderer_->SetIndex(84);

	IconRenderer_ = CreateRenderer(IMAGE_TOOL_SET1);
	IconRenderer_->SetIndex(89);
	IconRenderer_->CameraEffectOff();
}

void Axe::Update()
{
}