#include "SeedShop.h"
#include "ContentsEnums.h"
#include "ItemTable.h"
#include "Mouse.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>

SeedShop::SeedShop()
	: StockTop_(0),
	StockBot_(3),
	StockMax_(4)
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

	// 가격 설정
	StockPrice_[0] = 20;
	StockPrice_[1] = 50;
	StockPrice_[2] = 70;
	StockPrice_[3] = 80;
	StockPrice_[4] = 60;

	// 종류 설정
	StockType_[0] = (int)ITEMTABLE::PARSNIP;
	StockType_[1] = (int)ITEMTABLE::POTATO;
	StockType_[2] = (int)ITEMTABLE::KALE;
	StockType_[3] = (int)ITEMTABLE::COULIFLOWER;
	StockType_[4] = (int)ITEMTABLE::GREENBEAN;

	for (int i = 0; i <= StockMax_; i++)
	{
		StockCollision_[i] = CreateCollision(COL_GROUP_STOCK, { 1048.0f, 106.0f });

		StockCollision_[i]->Off();
	}

	for (size_t i = 0; i < 8; i++)
	{
		GoldFont_[i] = this->GetLevel()->CreateActor<Font>((int)ORDER::SEEDSHOP_FONT);
		GoldFont_[i]->GetRendererNumber()->SetOrder((int)ORDER::SEEDSHOP_FONT);
		GoldFont_[i]->RendererFontOff();
		GoldFont_[i]->RendererNumberOff();
	}

	ShopInventory_ = this->GetLevel()->CreateActor<Inventory>();

	// 키설정
	if (false == GameEngineInput::GetInst()->IsKey(KEY_CLOSE))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_CLOSE, VK_ESCAPE);
	}

}

void SeedShop::ShopStart()
{
	float4 tmpPos = GetLevel()->GetCameraPos();

	// 상점 틀 
	SeedShopInterfaceRender_->On();
	SeedShopInterfaceRender_->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
}

bool SeedShop::ShopUpdate()
{
	Player* tmpPlayer = static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER));
	float4 tmpPos = GetLevel()->GetCameraPos();
	int Num = static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER))->GetGold();

	// 휠을 위로
	if (120 == GameEngineInput::GetInst()->GetMouseWheel())
	{
		if (StockTop_ > 0)
		{
			StockTop_--;
			StockBot_--;
		}
	}
	// 휠을 아래로
	if (-120 == GameEngineInput::GetInst()->GetMouseWheel())
	{
		if (StockBot_ < StockMax_)
		{
			StockTop_++;
			StockBot_++;
		}
	}

	// 한번 모두 Off
	for (int i = 0; i <= StockMax_; i++)
	{
		SeedShopStockList_[i]->Off();
		StockCollision_[i]->Off();
	}

	int stockPos = 0;
	// 화면에 나오는 것들만 On
	for (int i = StockTop_; i <= StockBot_; i++)
	{
		// 메뉴
		SeedShopStockList_[i]->On();
		SeedShopStockList_[i]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 - 287 + (107 * stockPos) });

		// 충돌체
		StockCollision_[i]->On();
		StockCollision_[i]->SetPivot({ static_cast<float>(WINDOW_SIZE_W / 2) ,  static_cast<float>(WINDOW_SIZE_H / 2 - 287 + (107 * stockPos)) });

		stockPos++;
	}

	// 연속 동작 방지
	// 씨앗 구매
	if (this->GetAccTime() >= 0.1f)
	{
		if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
		{
			GameEngineCollision* MouseCol = static_cast<Mouse*>(GetLevel()->FindActor(ACTOR_MOUSE))->GetCollision();

			if (true == MouseCol->CollisionResult(COL_GROUP_STOCK, ResultCol_))
			{
				std::vector<GameEngineCollision*>::iterator StartCol = ResultCol_.begin();
				std::vector<GameEngineCollision*>::iterator EndCol = ResultCol_.end();

				for (; StartCol != EndCol; StartCol++)
				{
					for (int i = 0; i <= StockMax_; i++)
					{
						if (StockCollision_[i] == *StartCol)
						{
							// 돈이 충분히 있을때만
							if (tmpPlayer->GetGold() >= StockPrice_[i])
							{
								// 플레이어가 가지고 있는 돈을 깍음
								tmpPlayer->SetGold(Num - StockPrice_[i]);
								// 인벤토리에 아이템 추가
								tmpPlayer->GetInventory()->AddItemToInventory(StockType_[i]);
								tmpPlayer->GetInventory()->InventoryUpload();

								this->ReSetAccTime();

								break;
							}
						}
					}
				}

				// 결과 초기화
				ResultCol_.clear();
			}
		}
	}

	// 아래에 나오는 인벤토리 창
	// 렌더링용으로 복사
	// memcpy(Inventory_->GetInventoryList(), tmpPlayer->GetInventory()->GetInventoryList(), sizeof(tmpPlayer->GetInventory()->GetInventoryList()));

	float PosX = 0.0f, PosY = 0.0f;
	ShopInventory_->InventoryDownload();

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 12; j++)
		{
			PosX = IMAGE_INVENTORY_EXT_POS_X - (228 - (64 * (float)j));
			PosY = IMAGE_INVENTORY_EXT_POS_Y - (30 - (68 * (float)i));

			ShopInventory_->GetInventoryList()[j + (12 * i)]->GetIconRenderer().SetPivot({ PosX, PosY });
			ShopInventory_->GetInventoryList()[j + (12 * i)]->SetItemNum((int)ORDER::SEEDSHOP_FONT);
			ShopInventory_->GetInventoryList()[j + (12 * i)]->GetIconRenderer().On();
			ShopInventory_->GetInventoryList()[j + (12 * i)]->GetIconRenderer().SetOrder((int)ORDER::SEEDSHOP_ICONS);
		}
	}

	// 플레이어가 가지고 있는 돈
	for (size_t i = 8; i > 0; i--)
	{
		GoldFont_[i - 1]->RendererNumberOn();
		GoldFont_[i - 1]->GetNumberFont(Num % 10);
		GoldFont_[i - 1]->SetPosition({
									 tmpPos.x + 117 + (24.0f * i)
								   , tmpPos.y - 47 });
		Num /= 10;
	}

	// ESC로 종료
	if (true == GameEngineInput::GetInst()->IsDown(KEY_CLOSE))
	{
		SeedShopInterfaceRender_->Off();

		for (int i = 0; i <= StockMax_; i++)
		{
			SeedShopStockList_[i]->Off();
			StockCollision_[i]->Off();
		}

		for (int i = 0; i < 8; i++)
		{
			GoldFont_[i]->RendererNumberOff();
		}

		ShopInventory_->Death();
		ShopInventory_->FontDeath();

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