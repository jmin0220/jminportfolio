#include "Hoe.h"
#include "Inventory.h"

Hoe::Hoe() 
{
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
}

void Hoe::Update()
{
}