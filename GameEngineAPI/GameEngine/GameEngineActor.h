#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

// 설명 :
class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
{
public:
	friend GameEngineLevel;

	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	// 화면에서 액터의 위치
	inline float4 GetCameraEffectPosition()
	{
		return Position_ - GetLevel()->GetCameraPos();
	}

	inline float4 GetPosition()
	{
		return Position_;
	}

	inline float4 GetScale()
	{
		return Scale_;
	}

	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}

	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}

	inline void SetMove(float4 _Value)
	{
		Position_ += _Value;
	}

protected:
	virtual void Start() = 0;
	virtual void Update() {};
	virtual void Render() {};

	void Release();

	// 디버그용 4각형
	void DebugRectRender();

private:
	// 현재 액터가 생성되어있는 레벨
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;

	// 액터가 생성된 레벨의 정보를 설정
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

public:
	// 렌더러를 이미지 크기에 맞춰 생성
	GameEngineRenderer* CreateRenderer(RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	
	// 렌더러를 유저가 정한 크기에 맞춰 생성
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _Scale, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });

	void Rendering();

private:
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;
	std::list<GameEngineRenderer*> RenderList_;


///////////////////////////////////////////////////////// Collision
public:
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = { 0, 0 });

private:
	std::list<GameEngineCollision*> CollisionList_;

};

