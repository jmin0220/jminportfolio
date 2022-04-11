#pragma once
#include "PlayLevel.h"
#include "FarmBuilding.h"

// Ό³Έν :
class FarmLevel : public PlayLevel
{
public:
	// constrcuter destructer
	FarmLevel();
	~FarmLevel();

	// delete Function
	FarmLevel(const FarmLevel& _Other) = delete;
	FarmLevel(FarmLevel&& _Other) noexcept = delete;
	FarmLevel& operator=(const FarmLevel& _Other) = delete;
	FarmLevel& operator=(FarmLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	FarmBuilding* FarmBuilding_;
};

