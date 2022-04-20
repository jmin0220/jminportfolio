#include "Oaktree.h"
#include "ContentsEnums.h"

Oaktree::Oaktree() 
{
}

Oaktree::~Oaktree() 
{
}


void Oaktree::Start()
{
	Renderer_ = CreateRenderer(IMAGE_ENVIRONMENT_OAKTREE, (int)ORDER::FRONTA);
	Renderer_->SetIndex(0);
}