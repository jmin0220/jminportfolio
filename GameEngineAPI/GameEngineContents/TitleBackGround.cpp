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
	SetPosition({ 640, 360 });
	SetScale({ 1280, 720 });
}

void TitleBackGround::Render()
{
	DebugRectRender();
}