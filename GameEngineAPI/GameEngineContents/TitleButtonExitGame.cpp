#include "TitleButtonExitGame.h"

TitleButtonExitGame::TitleButtonExitGame()
{
}

TitleButtonExitGame::~TitleButtonExitGame()
{
}

void TitleButtonExitGame::Start()
{
	// Exit��ư�� ��ġ�� ũ��
	SetPosition({ 886, 608 });
	CreateRendererToScale("GameExit.bmp", { IMAGE_TITLE_BUTTON_W, IMAGE_TITLE_BUTTON_H });
}

void TitleButtonExitGame::Render()
{
}
