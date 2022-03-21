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
	// 타이틀로고의 위치와 크기
	SetPosition({640, 252});
	SetScale({ 796, 374});
}

void TitleLogo::Render()
{
	DebugRectRender();
}