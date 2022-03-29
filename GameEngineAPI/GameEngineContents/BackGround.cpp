#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

BackGround::BackGround() 
{
}

BackGround::~BackGround() 
{
}

void BackGround::Start()
{
	// 인트로메뉴 Background이미지의 위치와 크기
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	Image_ = CreateRenderer();
}

void BackGround::Render()
{
	// DebugRectRender();
}