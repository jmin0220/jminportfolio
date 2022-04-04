#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "BackGround.h"
#include "TitleButtonNewGame.h"
#include "TitleButtonLoadGame.h"
#include "TitleButtonExitGame.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}


void TitleLevel::Loading()
{
}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress(LEVEL_CHANGE_FARM))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_FARM);
	}
	if (true == GameEngineInput::GetInst()->IsPress(LEVEL_CHANGE_TOWN))
	{
		GameEngine::GetInst().ChangeLevel(LEVEL_TOWN);
	}
}

void TitleLevel::LevelChangeStart()
{
	BackGround* backGround = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	backGround->GetRenderer()->SetImage(IMAGE_TITLE_BACKGOUND);

	CreateActor<TitleLogo>((int)ORDER::UI);
	CreateActor<TitleButtonNewGame>((int)ORDER::UI);
	CreateActor<TitleButtonLoadGame>((int)ORDER::UI);
	CreateActor<TitleButtonExitGame>((int)ORDER::UI);

	GameEngineInput::GetInst()->CreateKey(LEVEL_CHANGE_FARM, '1');
	GameEngineInput::GetInst()->CreateKey(LEVEL_CHANGE_TOWN, '2');

}
