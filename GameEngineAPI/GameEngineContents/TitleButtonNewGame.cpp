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
	CreateRendererToScale("GameNew.bmp", { 222, 174 });
}

void TitleButtonNewGame::Render()
{
}