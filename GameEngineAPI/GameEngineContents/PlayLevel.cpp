#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "Clock.h"
#include "EnergyBar.h"
#include "Inventory.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>

BackGround* PlayLevel::BackGround_;
BackGround* PlayLevel::BGBuilding_;
BackGround* PlayLevel::BGBuildingCollision_;
BackGround* PlayLevel::BGFront_;
BackGround* PlayLevel::BGAlwaysFront_;

// UI구성
Inventory* PlayLevel::Inventory_;
Clock* PlayLevel::Clock_;
EnergyBar* PlayLevel::EnergyBar_;

// 플레이어
Player* PlayLevel::Player_;

PlayLevel::PlayLevel()
{
	// 배경
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	BGBuilding_ = CreateActor<BackGround>((int)ORDER::BUIDING);
	BGBuildingCollision_ = CreateActor<BackGround>((int)ORDER::COLLISION);
	BGFront_ = CreateActor<BackGround>((int)ORDER::FRONT);
	BGAlwaysFront_ = CreateActor<BackGround>((int)ORDER::ALWAYSFRONT);

	// UI
	Inventory_ = CreateActor<Inventory>((int)ORDER::UI);
	Clock_ = CreateActor<Clock>((int)ORDER::UI);
	EnergyBar_ = CreateActor<EnergyBar>((int)ORDER::UI);

	// 캐릭터
	Player_ = CreateActor<Player>((int)ORDER::PLAYER);
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	
}

void PlayLevel::Update()
{
}
