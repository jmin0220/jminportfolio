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
	GameEngineRenderer* StockRenderer_;
	GameEngineCollision* StockCollision_[4];

	// �÷��̾ ������ �ִ� ��
	Font* GoldFont_[8];
};

