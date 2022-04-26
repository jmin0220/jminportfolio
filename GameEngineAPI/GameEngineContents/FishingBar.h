#pragma once
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// ���� :
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


	// ���� ����
	bool SuccessFlg_;
	// ���� �������
	int ProgressLevel_;
	// �ʱ� UI��ġ
	float4 Pivot_;
	// �̵��ϴ� ���ӵ�
	float CatchBoxMoveSpeedY_;
	// ��Ȳ�� ���� �̵��ϴ� ����ġ
	float CatchBoxMovePivotY_;

	// ����UI
	GameEngineRenderer* Renderer_;
	// ������ ǥ�õ� ���¹�
	GameEngineRenderer* ProgressRenderer_;
	// �÷��̾ ��Ʈ���� ��Ʈ�ڽ�
	GameEngineRenderer* CatchboxRenderer_;
	// �÷��̾ ������� ������� ���
	GameEngineRenderer* LureRenderer_;

	// �÷��̾ ������ϴ� ����� �ø���
	GameEngineCollision* LureHitbox_;
	// �÷��̾ ��Ʈ���� ��Ʈ�ڽ��� �ø���
	GameEngineCollision* CatchHitbox_;

	// ����� ����
	LureState LureCurState_;
	// ����� �̵�����
	float LureMoveDirY_;
	float LurePosY_;
	int LureTimeCount_;

	GameEngineRandom* Random_;
};

