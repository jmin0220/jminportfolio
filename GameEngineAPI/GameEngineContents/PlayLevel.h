#pragma once
#include "BackGround.h"
#include "Clock.h"
#include "Inventory.h"
#include "EnergyBar.h"
#include "Player.h"
#include "PlayerTileIndex.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

// 설명 :
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

	float Time;

	GameEngineSoundPlayer BgmPlayer;

	std::vector<std::vector<PlayerTileIndex*>> GroundTiles_;
	std::vector<std::vector<PlayerTileIndex*>> EnvironmentTiles_;

protected:
	void Loading() override;
	void Update() override;

	Player* Player_;
	BackGround* BackGround_;
	BackGround* BGBuilding_;
	BackGround* BGFront_;
	BackGround* BGAlwaysFront_;

	// 타일 초기화
	void TileRangeSetting(int _X, int _Y);

private:
};

