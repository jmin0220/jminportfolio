#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "Clock.h"
#include "Player.h"
#include "EnergyBar.h"
#include "InventoryBar.h"
#include "ContentsEnums.h"

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
	CreateActor<Player>((int)ORDER::PLAYER);

	CreateActor<InventoryBar>((int)ORDER::UI);
	CreateActor<Clock>((int)ORDER::UI);
	CreateActor<EnergyBar>((int)ORDER::UI);
}