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

	// Ű����
	if (false == GameEngineInput::GetInst()->IsKey(KEY_CLOSE))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_CLOSE, VK_ESCAPE);
	}

}

void SeedShop::ShopStart()
{
	float4 tmpPos = GetLevel()->GetCameraPos();
	
	// ���� Ʋ 
	SeedShopInterfaceRender_->On();
	SeedShopInterfaceRender_->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 });
}

bool SeedShop::ShopUpdate()
{
	float4 tmpPos = GetLevel()->GetCameraPos();
	int Num = static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER))->GetGold();

	// ���� ����
	if (120 == GameEngineInput::GetInst()->GetMouseWheel())
	{
		if (StockTop_ > 0)
		{
			StockTop_--;
			StockBot_--;
		}
	}
	// ���� �Ʒ���
	if (-120 == GameEngineInput::GetInst()->GetMouseWheel())
	{
		if (StockBot_ < StockMax_)
		{
			StockTop_++;
			StockBot_++;
		}
	}

	// �ѹ� ��� Off
	for (int i = 0; i <= StockMax_; i++)
	{
		SeedShopStockList_[i]->Off();
	}

	int stockPos = 0;
	// ȭ�鿡 ������ �͵鸸 On
	for (int i = StockTop_; i <= StockBot_; i++)
	{
		// �޴�
		SeedShopStockList_[i]->On();
		SeedShopStockList_[i]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 - 287 + (107 * stockPos) });

		// �浹ü
		StockCollision_[i]->On();
		StockCollision_[i]->SetPivot({ tmpPos.x + WINDOW_SIZE_W / 2, tmpPos.y + WINDOW_SIZE_H / 2 - 287 + (107 * stockPos) });

		stockPos++;
	}

	// �÷��̾ ������ �ִ� ��
	for (size_t i = 8; i > 0; i--)
	{
		GoldFont_[i - 1]->RendererNumberOn();
		GoldFont_[i - 1]->GetNumberFont(Num % 10);
		GoldFont_[i - 1]->SetPosition({
									 tmpPos.x + 117 + (24.0f * i)
								   , tmpPos.y - 47 });

		Num /= 10;
	}



	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		GameEngineCollision* MouseCol = static_cast<Mouse*>(GetLevel()->FindActor(ACTOR_MOUSE))->GetCollision();

		for (size_t i = 0; i < 4; i++)
		{
			if (true == MouseCol->CollisionResult(COL_GROUP_STOCK, ResultCol_))
			{
				std::vector<GameEngineCollision*>::iterator StartCol = ResultCol_.begin();
				std::vector<GameEngineCollision*>::iterator EndCol = ResultCol_.end();

				for (; StartCol != EndCol; StartCol)
				{
					// ����
					//StartCol[0]->GetActor()->
				}

				static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER))->GetInventory()->AddItemToInventory(0);
				break;
			}
		}
	}


	// ESC�� ����
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