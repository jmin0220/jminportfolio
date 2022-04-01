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

// UI구성
Inventory* PlayLevel::Inventory_;
Clock* PlayLevel::Clock_;
EnergyBar* PlayLevel::EnergyBar_;

// 플레이어
Player* PlayLevel::Player_;

PlayLevel::PlayLevel()
{
	BackGround_ = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Inventory_ = CreateActor<Inventory>((int)ORDER::UI);
	Clock_ = CreateActor<Clock>((int)ORDER::UI);
	EnergyBar_ = CreateActor<EnergyBar>((int)ORDER::UI);
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


void PlayLevel::CameraUpdate()
{
	//if (Player_->GetPosition().y - GetCameraPos().y <= GameEngineWindow::GetInst().GetScale().y - 100.0f)
	//{
	//	SetCameraPos(Player_->GetPosition());
	//}
}