#pragma once
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineRandom.h>
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

	void GameStart();
	int GameUpdate();
	void GameEnd();

protected:
	void Start() override;

private:
	void LureUpdate();
	void LureStateChange(LureState _State);


	// 낚시 성공
	bool SuccessFlg_;
	// 낚시 진행상태
	int ProgressLevel_;
	// 초기 UI위치
	float4 Pivot_;
	// 이동하는 가속도
	float CatchBoxMoveSpeedY_;
	// 상황에 따라 이동하는 보정치
	float CatchBoxMovePivotY_;

	// 낚시UI
	GameEngineRenderer* Renderer_;
	// 우측에 표시될 상태바
	GameEngineRenderer* ProgressRenderer_;
	// 플레이어가 컨트롤할 히트박스
	GameEngineRenderer* CatchboxRenderer_;
	// 플레이어가 맞춰야할 물고기모양 루어
	GameEngineRenderer* LureRenderer_;

	// 플레이어가 맞춰야하는 루어의 컬리전
	GameEngineCollision* LureHitbox_;
	// 플레이어가 컨트롤할 히트박스의 컬리전
	GameEngineCollision* CatchHitbox_;

	// 루어의 상태
	LureState LureCurState_;
	// 루어의 이동방향
	float LureMoveDirY_;
	float LurePosY_;
	int LureTimeCount_;

	GameEngineRandom* Random_;
};

