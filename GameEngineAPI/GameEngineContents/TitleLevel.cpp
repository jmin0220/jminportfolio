#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "TitleButtonNewGame.h"
#include "TitleButtonLoadGame.h"
#include "TitleButtonExitGame.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>("TitleBackGround", 0);
	CreateActor<TitleLogo>("TitleLogo", 1);
	CreateActor<TitleButtonNewGame>("TitleButtonNewGame", 1);
	CreateActor<TitleButtonLoadGame>("TitleButtonLoadGame", 1);
	CreateActor<TitleButtonExitGame>("TitleButtonExitGame", 1);
}

void TitleLevel::Update()
{
	// GameEngine::GlobalEngine().ChangeLevel("Play");
}