#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include "FishingBar.h"
#include "FishingPowerbar.h"

// 설명 :
class FishingGame : public GameEngineActor
{
public:
	// constrcuter destructer
	FishingGame();
	~FishingGame();

	// delete Function
	FishingGame(const FishingGame& _Other) = delete;
	FishingGame(FishingGame&& _Other) noexcept = delete;
	FishingGame& operator=(const FishingGame& _Other) = delete;
	FishingGame& operator=(FishingGame&& _Other) noexcept = delete;

	void GameStart();
	bool GameUpdate();
	void GameEnd();
protected:
	void Start() override;
	

private:
	// 게임이 어디까지 진행중인가
	int PhaseFlg_;

	// 낚을 물고기 종류
	int FishType_;
	GameEngineRandom* FishRandom_;

	FishingBar* Fishingbar_;
	FishingPowerbar* FishingPowerbar_;

	GameEngineRenderer* FontMax_;
	GameEngineRenderer* FontHit_;

	GameEngineSoundPlayer Sound_;

};

