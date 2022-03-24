#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "Clock.h"
#include "Player.h"
#include "EnergyBar.h"
#include "InventoryBar.h"

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI
};

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
	CreateActor<Player>(ACTOR_PLAYER, (int)ORDER::PLAYER);

	CreateActor<InventoryBar>(ACTOR_UI_INVENTORY_BAR, (int)ORDER::UI);
	CreateActor<Clock>(ACTOR_UI_CLOCK, (int)ORDER::UI);
	CreateActor<EnergyBar>(ACTOR_UI_ENERGYBAR, (int)ORDER::UI);
}