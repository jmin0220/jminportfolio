#include "TitleButtonLoadGame.h"

TitleButtonLoadGame::TitleButtonLoadGame() 
{
}

TitleButtonLoadGame::~TitleButtonLoadGame() 
{
}

void TitleButtonLoadGame::Start()
{
	// LoadGame버튼의 위치와 크기
	SetPosition({ 640, 608 });
	CreateRendererToScale("GameLoad.bmp", { 222, 174 });
}

void TitleButtonLoadGame::Render()
{
	DebugRectRender();
}
