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
	SetScale({ 222, 174 });
}

void TitleButtonLoadGame::Render()
{
	DebugRectRender();
}
