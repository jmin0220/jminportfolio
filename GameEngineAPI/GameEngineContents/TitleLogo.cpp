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
	// Ÿ��Ʋ�α��� ��ġ�� ũ��
	SetPosition({640, 257});
	SetScale({ 400, 186});
}

void TitleLogo::Render()
{
	DebugRectRender();
}