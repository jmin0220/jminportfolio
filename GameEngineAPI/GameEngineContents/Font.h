#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

// Ό³Έν :
class Font : public GameEngineActor
{
public:
	// constrcuter destructer
	Font();
	~Font();

	// delete Function
	Font(const Font& _Other) = delete;
	Font(Font&& _Other) noexcept = delete;
	Font& operator=(const Font& _Other) = delete;
	Font& operator=(Font&& _Other) noexcept = delete;

	GameEngineRenderer* GetNumberFont(int _Index);

protected:
	void Start() override;

private:
	GameEngineRenderer* RendererNumber_;
};

