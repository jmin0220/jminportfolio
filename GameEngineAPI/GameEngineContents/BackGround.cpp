#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

BackGround::BackGround()
	: TileMap_(this)
{
}

BackGround::~BackGround() 
{
}

void BackGround::Start()
{
	Image_ = CreateRenderer();
}

void BackGround::Render()
{
	// DebugRectRender();
}