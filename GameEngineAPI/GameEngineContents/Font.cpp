#include "Font.h"
#include "ContentsEnums.h"

Font::Font() 
{
}

Font::~Font() 
{
}

void Font::Start()
{
	RendererNumber_ = CreateRenderer(IMAGE_FONT_NUMBER, (int)ORDER::UIFONT);
	RendererNumber_->CameraEffectOff();
}

GameEngineRenderer* Font::GetNumberFont(int _Index)
{
	RendererNumber_->SetIndex(_Index);

	return RendererNumber_;
}