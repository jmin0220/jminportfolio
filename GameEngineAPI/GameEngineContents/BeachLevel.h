#pragma once
#include "PlayLevel.h"

// Ό³Έν :
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
	void LevelChangeStart() override;

private:

};

