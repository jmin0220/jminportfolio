#include "TitleButtonNewGame.h"

TitleButtonNewGame::TitleButtonNewGame() 
{
}

TitleButtonNewGame::~TitleButtonNewGame()
{
}

void TitleButtonNewGame::Start()
{
	// NewGame버튼의 위치와 크기
	SetPosition({ 394, 608 });
	SetScale({ 222, 174 });
}

void TitleButtonNewGame::Render()
{
	DebugRectRender();
}