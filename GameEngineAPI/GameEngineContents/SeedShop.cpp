#include "SeedShop.h"
#include "ContentsEnums.h"
#include "ItemTable.h"
#include "Mouse.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>

SeedShop::SeedShop() 
{
}

SeedShop::~SeedShop() 
{
}

void SeedShop::Start()
{
	SeedShopInterfaceRender_ = CreateRenderer(IMAGE_SEEDSHOP_INTERFACE, (int)ORDER::SEEDSHOP_INTERFACE);
	SeedShopInterfaceRender_->Off();

	SeedShopStockList_[0] = CreateRenderer(IMAGE_SEEDSHOP_STOCK_PARSNIP,(int)ORDER::SEEDSHOP_ICONS);
	SeedShopStockList_[1] = CreateRenderer(IMAGE_SEEDSHOP_STOCK_POTATO, (int)ORDER::SEEDSHOP_ICONS);
	SeedShopStockList_[2] = CreateRenderer(IMAGE_SEEDSHOP_STOCK_KALE, (int)ORDER::SEEDSHOP_ICONS);
	SeedShopStockList_[3] = CreateRenderer(IMAGE_SEEDSHOP_STOCK_CAULIFLOWER, (int)ORDER::SEEDSHOP_ICONS);
	SeedShopStockList_[4] = CreateRenderer(IMAGE_SEEDSHOP_STOCK_GREENBEAN, (int)ORDER::SEEDSHOP_ICONS);

	SeedShopStockList_[0]->Off();
	SeedShopStockList_[1]->Off();
	SeedShopStockList_[2]->Off();
	SeedShopStockList_[3]->Off();
	SeedShopStockList_[4]->Off();

	StockCollision_[0] = CreateCollision(COL_GROUP_STOCK1, { 1048.0f, 106.0f});
	StockCollision_[1] = CreateCollision(COL_GROUP_STOCK2, { 1048.0f, 106.0f });
	StockCollision_[2] = CreateCollision(COL_GROUP_STOCK3, { 1048.0f, 106.0f });
	StockCollision_[3] = CreateCollision(COL_GROUP_STOCK4, { 1048.0f, 106.0f });

	StockCollision_[0]->Off();
	StockCollision_[1]->Off();
	StockCollision_[2]->Off();
	StockCollision_[3]->Off();

	for (size_t i = 0; i < 8; i++)
	{
		GoldFont_[i] = this->GetLevel()->CreateActor<Font>((int)ORDER::SEEDSHOP_FONT);
		GoldFont_[i]->GetRendererNumber()->SetOrder((int)ORDER::SEEDSHOP_FONT);
		GoldFont_[i]->RendererFontOff();
		GoldFont_[i]->RendererNumberOff();
	}

	// 키설정
	if (false == GameEngineInput::GetInst()->IsKey(KEY_CLOSE))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_CLOSE, VK_ESCAPE);
	}

}

void SeedShop::ShopStart()
{
	float4 tmpPos = GetLevel()->GetCameraPos();
	int Num = static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER))->GetGold();
	
	// 상점 틀 
	SeedShopInterfaceRender_->On();
	SeedShopInterfaceRender_->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });

	// 메뉴
	SeedShopStockList_[0]->On();
	SeedShopStockList_[1]->On();
	SeedShopStockList_[2]->On();
	SeedShopStockList_[3]->On();
	SeedShopStockList_[4]->On();

	SeedShopStockList_[0]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
	SeedShopStockList_[1]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
	SeedShopStockList_[2]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
	SeedShopStockList_[3]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
	SeedShopStockList_[4]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });

	// 마우스와의 충돌 판정
	StockCollision_[0]->On();
	StockCollision_[1]->On();
	StockCollision_[2]->On();
	StockCollision_[3]->On();

	StockCollision_[0]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
	StockCollision_[1]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
	StockCollision_[2]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
	StockCollision_[3]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });


	for (size_t i = 8; i > 0; i--)
	{
		GoldFont_[i - 1]->RendererNumberOn();
		GoldFont_[i - 1]->GetNumberFont(Num % 10);
		GoldFont_[i - 1]->SetPosition({
									 tmpPos.x + 117 + (24.0f * i)
								   , tmpPos.y - 47});

		Num /= 10;
	}
}

bool SeedShop::ShopUpdate()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (StockCollision_[i]->CollisionCheck(COL_GROUP_MOUSE))
			{
				static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER))->GetInventory()->AddItemToInventory(0);
				break;
			}
		}
	}


	// ESC로 종료
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CLOSE))
	{
		SeedShopInterfaceRender_->Off();

		SeedShopStockList_[0]->Off();
		SeedShopStockList_[1]->Off();
		SeedShopStockList_[2]->Off();
		SeedShopStockList_[3]->Off();
		SeedShopStockList_[4]->Off();

		StockCollision_[0]->Off();
		StockCollision_[1]->Off();
		StockCollision_[2]->Off();
		StockCollision_[3]->Off();
		return true;
	}

	return false;
}



void SeedShop::SetGold(int _Num)
{
	for (size_t i = 8; i > 0; i--)
	{
		GoldFont_[i - 1]->GetNumberFont(_Num % 10);
		GoldFont_[i - 1]->SetPosition({ 
									 IMAGE_CLOCK_POS_W - 91 + (24.0f * i)
								   , IMAGE_CLOCK_POS_H + 92 });

		_Num /= 10;
	}
}