#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "Clock.h"
#include "Player.h"
#include "EnergyBar.h"
#include "InventoryBar.h"
#include "ContentsEnums.h"
#include "BackGround.h"
#include <GameEngine/GameEngineRenderer.h>

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{

}

void PlayLevel::Update()
{
	//GameEngine::GlobalEngine().ChangeLevel("Exit");
}

void PlayLevel::LevelChangeStart()
{
	BackGround* backGround = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	backGround->GetRenderer()->SetImage("FarmBack.bmp");

	CreateActor<Player>((int)ORDER::PLAYER);

	CreateActor<InventoryBar>((int)ORDER::UI);
	CreateActor<Clock>((int)ORDER::UI);
	CreateActor<EnergyBar>((int)ORDER::UI);
}