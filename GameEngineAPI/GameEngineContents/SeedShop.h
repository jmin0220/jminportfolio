#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
class SeedShop : public GameEngineActor
{
public:
	// constrcuter destructer
	SeedShop();
	~SeedShop();

	// delete Function
	SeedShop(const SeedShop& _Other) = delete;
	SeedShop(SeedShop&& _Other) noexcept = delete;
	SeedShop& operator=(const SeedShop& _Other) = delete;
	SeedShop& operator=(SeedShop&& _Other) noexcept = delete;

	bool ShopUpdate();

protected:
	void Start() override;

private:
	// ���� �������̽�
	GameEngineRenderer* SeedShopInterfaceRender_;
	// ��ǰ
	GameEngineRenderer* StockRenderer_;
	GameEngineCollision* StockCollision_;
};

