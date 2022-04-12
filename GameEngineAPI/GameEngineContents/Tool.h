#pragma once
#include "Item.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

// ���� :
class Tool : public Item
{
public:
	// constrcuter destructer
	Tool();
	virtual ~Tool();

	// delete Function
	Tool(const Tool& _Other) = delete;
	Tool(Tool&& _Other) noexcept = delete;
	Tool& operator=(const Tool& _Other) = delete;
	Tool& operator=(Tool&& _Other) noexcept = delete;

	float Time;

protected:

	virtual void InventoryIcon() {};

private:
};

