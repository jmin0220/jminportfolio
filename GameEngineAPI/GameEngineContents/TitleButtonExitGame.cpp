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
	SetScale({ 222, 174 });
}

void TitleButtonExitGame::Render()
{
	DebugRectRender();
}
