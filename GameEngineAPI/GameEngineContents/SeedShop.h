#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"

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

	void ShopStart();
	bool ShopUpdate();
	void SetGold(int _Num);

protected:
	void Start() override;

private:
	// 상점 인터페이스
	GameEngineRenderer* SeedShopInterfaceRender_;
	GameEngineRenderer* SeedShopStockList_[5];

	// 상품
	GameEngineRenderer* StockRenderer_;
	GameEngineCollision* StockCollision_[4];

	// 플레이어가 가지고 있는 돈
	Font* GoldFont_[8];
};

