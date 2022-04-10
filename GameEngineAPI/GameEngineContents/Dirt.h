#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class Dirt : public GameEngineActor
{
public:
	// constrcuter destructer
	Dirt();
	~Dirt();

	// delete Function
	Dirt(const Dirt& _Other) = delete;
	Dirt(Dirt&& _Other) noexcept = delete;
	Dirt& operator=(const Dirt& _Other) = delete;
	Dirt& operator=(Dirt&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	GameEngineRenderer* Renderer;
};

