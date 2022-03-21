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
	// 윈도우의 초기 크기 세팅
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	// 리소스를 다 로드하지 못하는 상황이 올수가 없다.

	GameEngineImageManager::GetInst()->Load("C:\\Users\\JungminLee\\Documents\\assortrock\\portfolio\\jminportfolio\\GameEngineAPI\\Resources\\Image\\Idle.bmp", "Idle.bmp");

	// 레벨 생성
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");

	// 레벨 변경
	ChangeLevel("Title");
}

void StardewContents::GameLoop()
{
	// 레벨 변경
	ChangeLevel("Play");
}

void StardewContents::GameEnd()
{

}