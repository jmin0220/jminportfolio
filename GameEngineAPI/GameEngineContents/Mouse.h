#pragma once

#include <windows.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
// 설명 :
class Mouse : public GameEngineActor
{
public:

	// constrcuter destructer
	Mouse();
	~Mouse();

	// delete Function
	Mouse(const Mouse& _Other) = delete;
	Mouse(Mouse&& _Other) noexcept = delete;
	Mouse& operator=(const Mouse& _Other) = delete;
	Mouse& operator=(Mouse&& _Other) noexcept = delete;

protected:

public:
	GameEngineRenderer* GetRenderer() 
	{
		return MousePoint_;
	}

	GameEngineCollision* GetCollision() {
		return MouseCollision_;
	}

	void MouseOff() 
	{
		this -> Off();
	}

	bool IsMouseDown();
	bool IsMousePress();
	bool IsMouseFree();

	inline void SetHoldingItem(bool b) 
	{
		PressMouse_ = b;
	}

	inline bool GetHoldingItem() const
	{
		return PressMouse_;
	}

private:

	// 마우스 포인터의 정보
	POINT pt;
	// 마우스 포인터 위치
	float4 CursorPos_;
	// 포인터 렌더러
	GameEngineRenderer* MousePoint_;
	// 포인터 충돌체
	GameEngineCollision* MouseCollision_;
	std::vector<GameEngineCollision*> ColList;

	// 눌려있는지 판단
	bool PressMouse_;

	void Start() override;
	void Update() override;
	void Render() override;
};

