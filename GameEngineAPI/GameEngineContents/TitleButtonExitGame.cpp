#include "TitleButtonExitGame.h"

TitleButtonExitGame::TitleButtonExitGame()
{
}

TitleButtonExitGame::~TitleButtonExitGame()
{
}

void TitleButtonExitGame::Start()
{
	// Exit버튼의 위치와 크기
	SetPosition({ 886, 608 });
	CreateRendererToScale("GameExit.bmp", { 222, 174 });
}

void TitleButtonExitGame::Render()
{
}
