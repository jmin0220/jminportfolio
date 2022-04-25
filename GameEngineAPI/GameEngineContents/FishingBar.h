#pragma once
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

	int GameUpdate();

protected:
	void Start() override;

private:
	// ���� ����
	bool SuccessFlg_;
	// ���� �������
	int ProgressLevel_;
	float HitboxSpeed_;

	// ����UI
	GameEngineRenderer* Renderer_;
	// ������ ǥ�õ� ���¹�
	GameEngineRenderer* ProgressRenderer_;
	// �÷��̾ ��Ʈ���� ��Ʈ�ڽ�
	GameEngineRenderer* HitboxRenderer_;

	// �÷��̾ ������ϴ� ����� �������� �ø���
	GameEngineCollision* FishHitbox_;
	// �÷��̾ ��Ʈ���� ��Ʈ�ڽ��� �ø���
	GameEngineCollision* CatchHitbox_;
};

