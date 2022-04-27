#pragma once
#include <GameEngine/GameEngineActor.h>
#include "Font.h"

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

	void ShopStart();
	bool ShopUpdate();
	void SetGold(int _Num);

protected:
	void Start() override;

private:
	// ���� �������̽�
	GameEngineRenderer* SeedShopInterfaceRender_;
	GameEngineRenderer* SeedShopStockList_[5];

	// ��ǰ
	GameEngineCollision* StockCollision_[5];
	std::vector<GameEngineCollision*> ResultCol_;

	// �÷��̾ ������ �ִ� ��
	Font* GoldFont_[8];

	int StockTop_;
	int StockBot_;
	int StockMax_;
};

