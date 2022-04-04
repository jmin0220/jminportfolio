#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class FarmBuildingLevel : public PlayLevel
{
public:
	// constrcuter destructer
	FarmBuildingLevel();
	~FarmBuildingLevel();

	// delete Function
	FarmBuildingLevel(const FarmBuildingLevel& _Other) = delete;
	FarmBuildingLevel(FarmBuildingLevel&& _Other) noexcept = delete;
	FarmBuildingLevel& operator=(const FarmBuildingLevel& _Other) = delete;
	FarmBuildingLevel& operator=(FarmBuildingLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:

};

