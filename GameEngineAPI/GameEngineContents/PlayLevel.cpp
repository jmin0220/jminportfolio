#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "Clock.h"
#include "Player.h"
#include "EnergyBar.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<Player>("Player", 1);
	CreateActor<Clock>("Clock", 100);
	CreateActor<EnergyBar>("EnergyBar", 100);
}

void PlayLevel::Update()
{
	//GameEngine::GlobalEngine().ChangeLevel("Exit");
}