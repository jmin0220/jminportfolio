#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	// Ÿ��Ʋ�ΰ��� ��ġ�� ũ��
	SetPosition({640, 252});
	CreateRendererToScale("TitleLogo.bmp", { IMAGE_TITLE_LOGO_W, IMAGE_TITLE_LOGO_H});
}

void TitleLogo::Render()
{
	
}