#pragma once
#include "PlayLevel.h"

// ���� :
class BeachLevel : public PlayLevel
{
public:
	// constrcuter destructer
	BeachLevel();
	~BeachLevel();

	// delete Function
	BeachLevel(const BeachLevel& _Other) = delete;
	BeachLevel(BeachLevel&& _Other) noexcept = delete;
	BeachLevel& operator=(const BeachLevel& _Other) = delete;
	BeachLevel& operator=(BeachLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

};

