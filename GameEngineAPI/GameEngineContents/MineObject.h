#pragma once
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Item.h"

// ���� :
class MineObject : public Item
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

private:
	int ItemIndex_;
	GameEngineRenderer* Renderer_;
	Item* CreateItem();

	GameEngineRandom* RandomItem_;
};

