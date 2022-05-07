#pragma once
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Crops.h"

// 설명 :
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
	// 광석이 중복으로 생성되는것을 방지하기 위해
	static int PrevIndex_;

	// 파괴되었을때 아이템 생성
	Item* CreateItem();

	GameEngineRandom* RandomItem_;
};

