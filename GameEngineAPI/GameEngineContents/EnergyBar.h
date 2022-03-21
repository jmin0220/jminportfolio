#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class EnergyBar : public GameEngineActor
{
public:
	// constrcuter destructer
	EnergyBar();
	~EnergyBar();

	// delete Function
	EnergyBar(const EnergyBar& _Other) = delete;
	EnergyBar(EnergyBar&& _Other) noexcept = delete;
	EnergyBar& operator=(const EnergyBar& _Other) = delete;
	EnergyBar& operator=(EnergyBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;

private:

};

