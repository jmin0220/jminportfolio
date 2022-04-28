#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"
#include "Inventory.h"

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

	// 상품
	GameEngineRenderer* SeedShopStockList_[5];
	GameEngineCollision* StockCollision_[5];
	int StockPrice_[5];
	int StockType_[5];

	std::vector<GameEngineCollision*> ResultCol_;

	// 플레이어가 가지고 있는 돈
	Font* GoldFont_[8];
	Inventory* ShopInventory_;

	// 메뉴에 포함될 범위
	int StockTop_;
	int StockBot_;
	int StockMax_;
};

