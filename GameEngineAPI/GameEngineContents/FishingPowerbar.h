#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class FishingPowerbar : public GameEngineActor
{
public:
	// constrcuter destructer
	FishingPowerbar();
	~FishingPowerbar();

	// delete Function
	FishingPowerbar(const FishingPowerbar& _Other) = delete;
	FishingPowerbar(FishingPowerbar&& _Other) noexcept = delete;
	FishingPowerbar& operator=(const FishingPowerbar& _Other) = delete;
	FishingPowerbar& operator=(FishingPowerbar&& _Other) noexcept = delete;

	bool GameUpdate();

protected:
	void Start() override;

private:
	int Powerlevel_;
	int PowerlevelDir_;
	GameEngineRenderer* BarRenderer_;
};

