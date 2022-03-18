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
	// 타이틀로그의 위치와 크기
	SetPosition({640, 257});
	SetScale({ 400, 186});
}

void TitleLogo::Render()
{
	DebugRectRender();
}