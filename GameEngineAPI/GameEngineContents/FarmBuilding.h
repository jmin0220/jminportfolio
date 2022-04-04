#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class FarmBuilding : public GameEngineActor
{
public:
	// constrcuter destructer
	FarmBuilding();
	~FarmBuilding();

	// delete Function
	FarmBuilding(const FarmBuilding& _Other) = delete;
	FarmBuilding(FarmBuilding&& _Other) noexcept = delete;
	FarmBuilding& operator=(const FarmBuilding& _Other) = delete;
	FarmBuilding& operator=(FarmBuilding&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

