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
	SetScale({ 222, 174 });
}

void TitleButtonNewGame::Render()
{
	DebugRectRender();
}