#include "TitleButtonNewGame.h"

TitleButtonNewGame::TitleButtonNewGame() 
{
}

TitleButtonNewGame::~TitleButtonNewGame()
{
}

void TitleButtonNewGame::Start()
{
	// NewGame��ư�� ��ġ�� ũ��
	SetPosition({ 394, 608 });
	CreateRendererToScale("GameNew.bmp", { IMAGE_TITLE_BUTTON_W, IMAGE_TITLE_BUTTON_H });
}

void TitleButtonNewGame::Render()
{
}