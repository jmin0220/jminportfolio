#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleButtonNewGame : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleButtonNewGame();
	~TitleButtonNewGame();

	// delete Function
	TitleButtonNewGame(const TitleButtonNewGame& _Other) = delete;
	TitleButtonNewGame(TitleButtonNewGame&& _Other) noexcept = delete;
	TitleButtonNewGame& operator=(const TitleButtonNewGame& _Other) = delete;
	TitleButtonNewGame& operator=(TitleButtonNewGame&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;

private:

};

