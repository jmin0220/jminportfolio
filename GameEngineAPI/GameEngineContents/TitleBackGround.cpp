#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

TitleBackGround::TitleBackGround() 
{
}

TitleBackGround::~TitleBackGround() 
{
}

void TitleBackGround::Start()
{
	// 인트로메뉴 Background이미지의 위치와 크기
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("MainBackground.bmp");
}

void TitleBackGround::Render()
{
	// DebugRectRender();
}