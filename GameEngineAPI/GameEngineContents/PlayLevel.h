#pragma once
#include "BackGround.h"
#include "Clock.h"
#include "Inventory.h"
#include "EnergyBar.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

	static Player* Player_;
	static BackGround* BackGround_;
	static BackGround* BGBuilding_;
	static BackGround* BGBuildingCollision_;
	static BackGround* BGFront_;
	static BackGround* BGAlwaysFront_;
	static Inventory* Inventory_;
	static Clock* Clock_;
	static EnergyBar* EnergyBar_;

private:
};

