#pragma once
#include <GameEngine/GameEngineActor.h>

// 설명 :
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
	// 상점 인터페이스
	GameEngineRenderer* SeedShopInterfaceRender_;
	// 상품
	GameEngineRenderer* StockRenderer_;
	GameEngineCollision* StockCollision_;
};

