#pragma once
#include "PlayLevel.h"

// Ό³Έν :
class Cave2 : public PlayLevel
{
public:
	// constrcuter destructer
	Cave2();
	~Cave2();

	// delete Function
	Cave2(const Cave2& _Other) = delete;
	Cave2(Cave2&& _Other) noexcept = delete;
	Cave2& operator=(const Cave2& _Other) = delete;
	Cave2& operator=(Cave2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

};