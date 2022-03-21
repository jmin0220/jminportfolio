#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleButtonLoadGame : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleButtonLoadGame();
	~TitleButtonLoadGame();

	// delete Function
	TitleButtonLoadGame(const TitleButtonLoadGame& _Other) = delete;
	TitleButtonLoadGame(TitleButtonLoadGame&& _Other) noexcept = delete;
	TitleButtonLoadGame& operator=(const TitleButtonLoadGame& _Other) = delete;
	TitleButtonLoadGame& operator=(TitleButtonLoadGame&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Render() override;
private:

};

