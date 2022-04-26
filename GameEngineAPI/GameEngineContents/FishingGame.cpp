#include "FishingGame.h"
#include "ItemTable.h"
#include "ContentsEnums.h"
#include "Player.h"


FishingGame::FishingGame()
	: PhaseFlg_(0)
{
	FishRandom_ = new GameEngineRandom();
}

FishingGame::~FishingGame() 
{
	delete FishRandom_;
	FishRandom_ = nullptr;
}

void FishingGame::Start()
{
	FontMax_ = CreateRenderer(IMAGE_FISHING_MAX, (int)ORDER::UI);
	FontMax_->SetPivot({ -50.0f, 0.0f });
	FontMax_->Off();

	FontHit_ = CreateRenderer(IMAGE_FISHING_HIT, (int)ORDER::UI);
	FontHit_->SetPivot({ -50.0f, 0.0f });
	FontHit_->Off();
}

bool FishingGame::GameUpdate()
{
	bool FishingEndFlg = false;
	int UpdateResult = 0;
	this->AddAccTime(GameEngineTime::GetDeltaTime());

	switch (PhaseFlg_)
	{
	// ��������
	case 0:
		FishingEndFlg = true;
		break;
	// ���ø� ������ ������
	case 1:

		if (true == FishingPowerbar_->GameUpdate())
		{
			PhaseFlg_ = 2;
			FishingPowerbar_->GameEnd();
			Fishingbar_->GameStart();
		}

		this->ReSetAccTime();
		break;
	// ���ð�����
	case 2:
		// ���� ����� �Ѿ������ 1�� ������
		if (this->GetAccTime() <= 1.0)
		{
			break;
		}

		UpdateResult = Fishingbar_->GameUpdate();

		// ���� ����
		if (1 == UpdateResult)
		{
			PhaseFlg_ = 3;
			Fishingbar_->GameEnd();
		}
		else if (2 == UpdateResult)
		{
			PhaseFlg_ = 4;
			Fishingbar_->GameEnd();
		}
		break;
	// ��� & ������ ���
	case 3:
		// ���� ����� �Ѿ������ 1�� ������
		if (this->GetAccTime() <= 1.0)
		{
			break;
		}

		FishType_ = FishRandom_->RandomInt((int)ITEMTABLE::PUFFERFISH, (int)ITEMTABLE::ANCHOVY);

		static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER))->GetInventory()->AddItemToInventory(FishType_);

		PhaseFlg_ = 0;
		break;
	// ����
	case 4:
		FishingEndFlg = true;
		break;
	default:
		FishingEndFlg = true;
		break;
	}

	// false == ������
	// true	 == ���� ����
	return FishingEndFlg;
}

void FishingGame::GameStart()
{
	// ������ �����Ҷ� UI���� ����
	Fishingbar_ = GetLevel()->CreateActor<FishingBar>();
	FishingPowerbar_ = GetLevel()->CreateActor<FishingPowerbar>();

	// ���� ����
	PhaseFlg_ = 1;
	FishingPowerbar_->GameStart();
}

void FishingGame::GameEnd()
{
	// ������ ������ UI���� �Ҹ�
	Fishingbar_->Death();
	FishingPowerbar_->Death();
}