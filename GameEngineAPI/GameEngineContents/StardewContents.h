#pragma once
#include <GameEngine/GameEngine.h>

// ���� :
class StardewContents : public GameEngine
{
public:
	// constrcuter destructer
	StardewContents();
	~StardewContents();

	// delete Function
	StardewContents(const StardewContents& _Other) = delete;
	StardewContents(StardewContents&& _Other) noexcept = delete;
	StardewContents& operator=(const StardewContents& _Other) = delete;
	StardewContents& operator=(StardewContents&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd() override;


protected:

private:
};

