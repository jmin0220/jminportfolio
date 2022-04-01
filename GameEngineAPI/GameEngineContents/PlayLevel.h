#pragma once
#include "BackGround.h"
#include "Clock.h"
#include "Inventory.h"
#include "EnergyBar.h"
#include "Player.h"
#include <GameEngine/GameEngineLevel.h>

// ���� :
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
	void CameraUpdate();

	static Player* Player_;
	static BackGround* BackGround_;
	static Inventory* Inventory_;
	static Clock* Clock_;
	static EnergyBar* EnergyBar_;

private:
};

