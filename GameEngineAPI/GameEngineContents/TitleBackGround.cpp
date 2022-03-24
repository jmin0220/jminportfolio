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
	SetPosition({ 640, 360 });
	SetScale({ IMAGE_FULL_SIZE_W, IMAGE_FULL_SIZE_H });
}

void TitleBackGround::Render()
{
	DebugRectRender();
}