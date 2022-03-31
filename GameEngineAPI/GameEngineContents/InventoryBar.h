#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class InventoryBar : public GameEngineActor
{
public:
	// constrcuter destructer
	InventoryBar();
	~InventoryBar();

	// delete Function
	InventoryBar(const InventoryBar& _Other) = delete;
	InventoryBar(InventoryBar&& _Other) noexcept = delete;
	InventoryBar& operator=(const InventoryBar& _Other) = delete;
	InventoryBar& operator=(InventoryBar&& _Other) noexcept = delete;

	void SetPos(float4 _Pos);

protected:
	void Start() override;
	void Update() override;

private:
	float4 Pos_;
};

