#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class MineLevel : public PlayLevel
{
public:
	// constrcuter destructer
	MineLevel();
	~MineLevel();

	// delete Function
	MineLevel(const MineLevel& _Other) = delete;
	MineLevel(MineLevel&& _Other) noexcept = delete;
	MineLevel& operator=(const MineLevel& _Other) = delete;
	MineLevel& operator=(MineLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

};

