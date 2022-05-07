#pragma once
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Crops.h"

// ���� :
class MineObject : public Crops
{
public:
	// constrcuter destructer
	MineObject();
	~MineObject();

	// delete Function
	MineObject(const MineObject& _Other) = delete;
	MineObject(MineObject&& _Other) noexcept = delete;
	MineObject& operator=(const MineObject& _Other) = delete;
	MineObject& operator=(MineObject&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;

private:
	int ItemIndex_;
	// ������ �ߺ����� �����Ǵ°��� �����ϱ� ����
	static int PrevIndex_;

	// �ı��Ǿ����� ������ ����
	Item* CreateItem();

	GameEngineRandom* RandomItem_;
};

