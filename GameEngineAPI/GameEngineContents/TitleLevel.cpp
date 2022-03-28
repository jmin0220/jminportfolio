#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "TitleButtonNewGame.h"
#include "TitleButtonLoadGame.h"
#include "TitleButtonExitGame.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

enum class ORDER
{
	BACKGROUND,
	UI
};
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
		//GameEngine::GlobalEngine().ChangeLevel(LEVEL_PLAY);
	}
	// GameEngine::GlobalEngine().ChangeLevel("Play");
}

void TitleLevel::LevelChangeStart()
{
	CreateActor<TitleBackGround>((int)ORDER::BACKGROUND);
	CreateActor<TitleLogo>((int)ORDER::UI);
	CreateActor<TitleButtonNewGame>((int)ORDER::UI);
	CreateActor<TitleButtonLoadGame>((int)ORDER::UI);
	CreateActor<TitleButtonExitGame>((int)ORDER::UI);

	if (false == GameEngineInput::GetInst()->IsKey(LEVEL_CHANGE))
	{
		GameEngineInput::GetInst()->CreateKey(LEVEL_CHANGE, VK_LBUTTON);
	}
}
