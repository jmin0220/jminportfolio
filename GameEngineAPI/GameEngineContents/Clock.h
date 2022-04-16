#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Font.h"

// Ό³Έν :
class Clock : public GameEngineActor
{
public:
	// constrcuter destructer
	Clock();
	~Clock();

	// delete Function
	Clock(const Clock& _Other) = delete;
	Clock(Clock&& _Other) noexcept = delete;
	Clock& operator=(const Clock& _Other) = delete;
	Clock& operator=(Clock&& _Other) noexcept = delete;

	void SetGold(int _Num);

protected:
	void Start() override;

private:
	Font* GoldFont_[8];
};

