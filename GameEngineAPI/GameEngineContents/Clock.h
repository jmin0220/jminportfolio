#pragma once
#include <GameEngine/GameEngineActor.h>

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

protected:
	void Start() override;
	void Render() override;

private:

};

