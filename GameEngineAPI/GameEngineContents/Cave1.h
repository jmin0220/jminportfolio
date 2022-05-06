#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class Cave1 : public PlayLevel
{
public:
	// constrcuter destructer
	Cave1();
	~Cave1();

	// delete Function
	Cave1(const Cave1& _Other) = delete;
	Cave1(Cave1&& _Other) noexcept = delete;
	Cave1& operator=(const Cave1& _Other) = delete;
	Cave1& operator=(Cave1&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
};

