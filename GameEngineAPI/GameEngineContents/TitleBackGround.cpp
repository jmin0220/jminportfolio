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
	SetScale({ IMAGE_FULL_SIZE_W, IMAGE_FULL_SIZE_H });
}

void TitleBackGround::Render()
{
	DebugRectRender();
}