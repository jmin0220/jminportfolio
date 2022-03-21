#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleButtonExitGame : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleButtonExitGame();
	~TitleButtonExitGame();

	// delete Function
	TitleButtonExitGame(const TitleButtonExitGame& _Other) = delete;
	TitleButtonExitGame(TitleButtonExitGame&& _Other) noexcept = delete;
	TitleButtonExitGame& operator=(const TitleButtonExitGame& _Other) = delete;
	TitleButtonExitGame& operator=(TitleButtonExitGame&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;

private:

};

