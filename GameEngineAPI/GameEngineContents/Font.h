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

	GameEngineRenderer* GetFont(char _Char);
	GameEngineRenderer* GetNumberFont(int _Index);

	inline void RendererFontOff()
	{
		RendererFont_->Off();
	}
	inline void RendererFontOn()
	{
		RendererFont_->On();
	}
	inline void RendererNumberOff()
	{
		RendererNumber_->Off();
	}
	inline void RendererNumberOn()
	{
		RendererNumber_->On();
	}

	inline GameEngineRenderer* GetRendererFont()
	{
		return RendererFont_;
	}

	inline GameEngineRenderer* RendererNumber()
	{
		return RendererNumber_;
	}

protected:
	void Start() override;

	GameEngineRenderer* RendererFont_;
	GameEngineRenderer* RendererNumber_;
private:
};

