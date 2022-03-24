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
	CreateActor<TitleBackGround>(ACTOR_TITLE_BACKGROUND, (int)ORDER::BACKGROUND);
	CreateActor<TitleLogo>(ACTOR_TITLE_LOGO, (int)ORDER::UI);
	CreateActor<TitleButtonNewGame>(ACTOR_TITLE_BUTTON_NEW, (int)ORDER::UI);
	CreateActor<TitleButtonLoadGame>(ACTOR_TITLE_BUTTON_LOAD, (int)ORDER::UI);
	CreateActor<TitleButtonExitGame>(ACTOR_TITLE_BUTTON_EXIT, (int)ORDER::UI);

	if (false == GameEngineInput::GetInst()->IsKey(LEVEL_CHANGE))
	{
		GameEngineInput::GetInst()->CreateKey(LEVEL_CHANGE, VK_LBUTTON);
	}
}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress(LEVEL_CHANGE))
	{
		GameEngine::GlobalEngine().ChangeLevel(LEVEL_PLAY);
	}
	// GameEngine::GlobalEngine().ChangeLevel("Play");
}