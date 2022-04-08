#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "Clock.h"
#include "EnergyBar.h"
#include "Inventory.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Hoe.h"

PlayLevel::PlayLevel()
{
	// UI
	Inventory_ = CreateActor<Inventory>((int)ORDER::UI);
	Clock_ = CreateActor<Clock>((int)ORDER::UI);
	EnergyBar_ = CreateActor<EnergyBar>((int)ORDER::UI);

	// Ä³¸¯ÅÍ
	Player_ = CreateActor<Player>((int)ORDER::PLAYER);



	Hoe* hoeTest = CreateActor<Hoe>();
	Inventory_->AddItemToInventory(*hoeTest);
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
}

void PlayLevel::Update()
{
	Time -= GameEngineTime::GetDeltaTime();

	if (0 >= Time)
	{
		BgmPlayer.Stop();
	}
}
