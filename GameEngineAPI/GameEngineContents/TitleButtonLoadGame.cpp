#include "TitleButtonLoadGame.h"

TitleButtonLoadGame::TitleButtonLoadGame() 
{
}

TitleButtonLoadGame::~TitleButtonLoadGame() 
{
}

void TitleButtonLoadGame::Start()
{
	// LoadGame��ư�� ��ġ�� ũ��
	SetPosition({ 640, 608 });
	CreateRendererToScale("GameLoad.bmp", { IMAGE_TITLE_BUTTON_W, IMAGE_TITLE_BUTTON_H });
}

void TitleButtonLoadGame::Render()
{
	DebugRectRender();
}
