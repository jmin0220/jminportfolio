#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// 설명 :
class FishingBar : public GameEngineActor
{
public:
	// constrcuter destructer
	FishingBar();
	~FishingBar();

	// delete Function
	FishingBar(const FishingBar& _Other) = delete;
	FishingBar(FishingBar&& _Other) noexcept = delete;
	FishingBar& operator=(const FishingBar& _Other) = delete;
	FishingBar& operator=(FishingBar&& _Other) noexcept = delete;

	int GameUpdate();

protected:
	void Start() override;

private:
	// 낚시 성공
	bool SuccessFlg_;
	// 낚시 진행상태
	int ProgressLevel_;
	float HitboxSpeed_;

	// 낚시UI
	GameEngineRenderer* Renderer_;
	// 우측에 표시될 상태바
	GameEngineRenderer* ProgressRenderer_;
	// 플레이어가 컨트롤할 히트박스
	GameEngineRenderer* HitboxRenderer_;

	// 플레이어가 맞춰야하는 물고기 아이콘의 컬리전
	GameEngineCollision* FishHitbox_;
	// 플레이어가 컨트롤할 히트박스의 컬리전
	GameEngineCollision* CatchHitbox_;
};

