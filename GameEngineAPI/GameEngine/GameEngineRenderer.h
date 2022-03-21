#pragma once
#include "GameEngineImage.h"
#include "GameEngineEnum.h"

// Ό³Έν :
class GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType = _Type;
	}

	void SetImage(const std::string& _Name);

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType;
};

