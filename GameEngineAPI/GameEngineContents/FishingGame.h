#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include "FishingBar.h"
#include "FishingPowerbar.h"

// ���� :
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
	// ������ ������ �������ΰ�
	int PhaseFlg_;

	// ���� ����� ����
	int FishType_;
	GameEngineRandom* FishRandom_;

	FishingBar* Fishingbar_;
	FishingPowerbar* FishingPowerbar_;

	GameEngineRenderer* FontMax_;
	GameEngineRenderer* FontHit_;

	GameEngineSoundPlayer Sound_;

};

