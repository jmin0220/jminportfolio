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

void Parsnip::Destroy()
{
	this->Death();
}