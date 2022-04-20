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
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_CROPS, (int)ORDER::FRONTA);
	Renderer_->SetIndex(0);
}