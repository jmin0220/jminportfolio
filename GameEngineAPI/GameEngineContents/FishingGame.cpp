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
	FontMax_ = CreateRenderer(IMAGE_FISHING_MAX, (int)ORDER::FISHINGUI);
	FontMax_->SetPivot({ -50.0f, 0.0f });
	FontMax_->Off();

	FontHit_ = CreateRenderer(IMAGE_FISHING_HIT, (int)ORDER::FISHINGUI);
	FontHit_->SetPivot({ -50.0f, 0.0f });
	FontHit_->Off();
}

bool FishingGame::GameUpdate()
{
	bool FishingEndFlg = false;
	int UpdateResult = 0;
	this->AddAccTime(GameEngineTime::GetDeltaTime());
	Player* TmpPlayer_ = static_cast<Player*>(GetLevel()->FindActor(ACTOR_PLAYER));
	std::string Dir = "";

	switch (PhaseFlg_)
	{
		// �÷��̾� �ִϸ��̼� ����
	case 0:
		if (float4::RIGHT.CompareInt2D(TmpPlayer_->GetMoveDir()))
		{
			Dir = ANIM_KEYWORD_DIR_RIGHT;
		}
		else if (float4::LEFT.CompareInt2D(TmpPlayer_->GetMoveDir()))
		{
			Dir = ANIM_KEYWORD_DIR_LEFT;
		}
		else if (float4::UP.CompareInt2D(TmpPlayer_->GetMoveDir()))
		{
			Dir = ANIM_KEYWORD_DIR_UP;
		}
		else if (float4::DOWN.CompareInt2D(TmpPlayer_->GetMoveDir()))
		{
			Dir = ANIM_KEYWORD_DIR_DOWN;
		}

		TmpPlayer_->PlayerAnimationChange(ANIM_KEYWORD_FISHING_WAIT + Dir);
		TmpPlayer_->ToolAnimationChange(ANIM_KEYWORD_TOOL_FISHING_WAIT + Dir);

		GameEngineSound::SoundPlayOneShot(SOUND_FISHBITE);

		PhaseFlg_ = 1;
		break;
		// ���ø� ������ ������
	case 1:

		if (true == FishingPowerbar_->GameUpdate())
		{
			PhaseFlg_ = 2;
			FishingPowerbar_->GameEnd();
			Fishingbar_->GameStart();
			Sound_ = GameEngineSound::SoundPlayControl(SOUND_REEL);
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

			Sound_.Stop();
		}
		else if (2 == UpdateResult)
		{
			PhaseFlg_ = 4;
			Fishingbar_->GameEnd();
			
			Sound_.Stop();
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

		TmpPlayer_->GetInventory()->AddItemToInventory(FishType_);

		PhaseFlg_ = 4;
		break;
		// ���� ����
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
	PhaseFlg_ = 0;
	FishingPowerbar_->GameStart();

}

void FishingGame::GameEnd()
{
	// ������ ������ UI���� �Ҹ�
	Fishingbar_->Death();
	FishingPowerbar_->Death();
}