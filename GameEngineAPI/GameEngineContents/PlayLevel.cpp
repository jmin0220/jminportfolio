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
	CreateActor<Player>("Player", (int)ORDER::PLAYER);

	CreateActor<InventoryBar>("InventoryBar", (int)ORDER::UI);
	CreateActor<Clock>("Clock", (int)ORDER::UI);
	CreateActor<EnergyBar>("EnergyBar", (int)ORDER::UI);
}