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
	CreateRendererToScale("GameLoad.bmp", { IMAGE_TITLE_BUTTON_W, IMAGE_TITLE_BUTTON_H });
}

void TitleButtonLoadGame::Render()
{
	//DebugRectRender();
}
