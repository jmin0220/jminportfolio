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
	// ��Ʈ�θ޴� Background�̹����� ��ġ�� ũ��
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("MainBackground.bmp");
}

void TitleBackGround::Render()
{
	// DebugRectRender();
}