#include "StardewContents.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

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

	// 레벨 생성
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");

	// 레벨 변경
	ChangeLevel("Title");
}

void StardewContents::GameLoop()
{

}

void StardewContents::GameEnd()
{

}