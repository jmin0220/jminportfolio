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
	SetScale({ 796, 374});
}

void TitleLogo::Render()
{
	DebugRectRender();
}