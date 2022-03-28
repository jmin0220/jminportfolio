#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"

// 설명 :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}
	
	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	// 이미지의 크기대로 출력
	void SetImageScale();

	// 유저가 설정한 크기대로 출력
	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index, float4 _Scale = {-1.0f, -1.0f });

protected:
	void Render();

private:
	// 출력할 이미지
	GameEngineImage* Image_;
	// 출력할 이미지의 기준점(Pivot)
	RenderPivot PivotType_;
	// 이미지크기대로 또는 사용자가 설정한 크기로
	RenderScaleMode ScaleMode_;

	float4 RenderPivot_;
	float4 RenderScale_;

	float4 RenderImageScale_;
	float4 RenderImagePivot_;

	unsigned int TransColor_;
};

