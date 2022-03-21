#include "StardewContents.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

StardewContents::StardewContents() 
{
}

StardewContents::~StardewContents() 
{
}

void StardewContents::GameInit()
{
	// �������� �ʱ� ũ�� ����
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	// ���ҽ��� �� �ε����� ���ϴ� ��Ȳ�� �ü��� ����.

	GameEngineImageManager::GetInst()->Load("C:\\Users\\JungminLee\\Documents\\assortrock\\portfolio\\jminportfolio\\GameEngineAPI\\Resources\\Image\\Idle.bmp", "Idle.bmp");

	// ���� ����
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");

	// ���� ����
	ChangeLevel("Title");
}

void StardewContents::GameLoop()
{
	// ���� ����
	ChangeLevel("Play");
}

void StardewContents::GameEnd()
{

}