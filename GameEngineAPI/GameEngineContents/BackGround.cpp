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
	// ��Ʈ�θ޴� Background�̹����� ��ġ�� ũ��
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	Image_ = CreateRenderer();
}

void BackGround::Render()
{
	// DebugRectRender();
}