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
	if (true == GameEngineInput::GetInst()->IsPress(LEVEL_CHANGE))
	{
		GameEngine::GlobalEngine().ChangeLevel(LEVEL_FARM);
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

	GameEngineInput::GetInst()->CreateKey(LEVEL_CHANGE, '1');

}
