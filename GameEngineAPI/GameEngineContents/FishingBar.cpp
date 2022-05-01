#include "FishingBar.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>

FishingBar::FishingBar()
	: SuccessFlg_(false)
	, ProgressLevel_(40)
	, CatchBoxMoveSpeedY_(0.0f)
	, CatchBoxMovePivotY_(0.0f)
	, LureMoveDirY_(1.0f)
	, LurePosY_(0.0f)
	, LureCurState_(LureState::MoveUp)
	, LureTimeCount_(0)
{
}

FishingBar::~FishingBar()
{
}

void FishingBar::Start()
{
	Renderer_ = CreateRenderer(IMAGE_FISHING_FISHINGBAR, (int)ORDER::FISHINGUI);
	Renderer_->Off();

	ProgressRenderer_ = CreateRenderer(IMAGE_FISHING_PROGRESS, (int)ORDER::FISHINGICONS);
	ProgressRenderer_->Off();

	CatchboxRenderer_ = CreateRenderer(IMAGE_FISHING_CATCH_HITBOX, (int)ORDER::FISHINGICONS);
	CatchboxRenderer_->Off();

	LureRenderer_ = CreateRenderer(IMAGE_FISHING_FISH_HITBOX, (int)ORDER::FISHINGLURE);
	LureRenderer_->Off();

	LureHitbox_ = CreateCollision(COL_GROUP_FISH_HITBOX, { 30.0f, 30.0f });
	CatchHitbox_ = CreateCollision(COL_GROUP_CATCH_HITBOX, { 27.0f, 108.0f });

	ProgressRenderer_->SetIndex(ProgressLevel_ - 1);

}

void FishingBar::GameStart()
{
	Pivot_ = static_cast<Player*>(this->GetLevel()->FindActor(ACTOR_PLAYER))->GetPosition();

	Renderer_->On();
	ProgressRenderer_->On();
	CatchboxRenderer_->On();
	LureRenderer_->On();

	Renderer_->SetPivot({ Pivot_.x + 100.0f, Pivot_.y });
	ProgressRenderer_->SetPivot({ Pivot_.x + 143.0f, Pivot_.y });
	CatchboxRenderer_->SetPivot({ Pivot_.x + 106.0f, Pivot_.y });
	LureRenderer_->SetPivot({ Pivot_.x + 106.0f, Pivot_.y });

	Random_ = new GameEngineRandom;
}

void FishingBar::GameEnd()
{
	Renderer_->Off();
	ProgressRenderer_->Off();
	CatchboxRenderer_->Off();
	LureRenderer_->Off();

	delete Random_;
	Random_ = nullptr;
}

int FishingBar::GameUpdate()
{
	int EndFlg = 0;
	this->AddAccTime(GameEngineTime::GetDeltaTime());

	// 클릭할때마다 상승
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		CatchBoxMoveSpeedY_ += 4.0f;

		// 최대속도
		if (CatchBoxMoveSpeedY_ >= 25.0f)
		{
			CatchBoxMoveSpeedY_ = 25.0f;
		}
	}

	// 0.1초 단위로 갱신됨
	if (this->GetAccTime() >= 0.1f)
	{
		CatchBoxMoveSpeedY_ -= 1.0f;

		// 최저속도
		if (CatchBoxMoveSpeedY_ <= 0.0f)
		{
			CatchBoxMoveSpeedY_ = 0.0f;
		}
	}


	// 기본적으로 하락
	CatchBoxMovePivotY_ += 2.0f;
	CatchBoxMovePivotY_ -= CatchBoxMoveSpeedY_;

	if (CatchBoxMovePivotY_ >= +150.0f)
	{
		CatchBoxMovePivotY_ = +150.0f;
	}

	if (CatchBoxMovePivotY_ <= -150.0f)
	{
		CatchBoxMovePivotY_ = -150.0f;
	}

	CatchboxRenderer_->SetPivot({ Pivot_.x + 106.0f, Pivot_.y + CatchBoxMovePivotY_ });
	CatchHitbox_->SetPivot({ Pivot_.x + 106.0f, Pivot_.y + CatchBoxMovePivotY_ });


	// 루어의 위치 업데이트
	LureUpdate();

	// 0.1초 단위로 갱신됨
	if (this->GetAccTime() >= 0.1f)
	{
		// 겹쳐지고 있으면 프로그레스바가 증가함
		if (true == CatchHitbox_->CollisionCheck(COL_GROUP_FISH_HITBOX, CollisionType::Rect, CollisionType::Rect))
		{
			ProgressLevel_++;

			if (ProgressLevel_ >= 100)
			{
				ProgressLevel_ = 101;
			}

			ProgressRenderer_->SetIndex(ProgressLevel_ - 1);
		}
		else
		{
			ProgressLevel_ -= 2;

			if (ProgressLevel_ <= 0)
			{
				ProgressLevel_ = 1;
			}

			ProgressRenderer_->SetIndex(ProgressLevel_ - 1);
		}

		ReSetAccTime();
	}

	// 낚시성공
	if (ProgressLevel_ >= 99)
	{
		EndFlg = 1;
	}
	// 낚시 실패
	else if (ProgressLevel_ <= 1)
	{
		EndFlg = 2;
	}

	return EndFlg;
}

void FishingBar::LureUpdate()
{

	LureRenderer_->SetPivot({ Pivot_.x + 106.0f, Pivot_.y + LurePosY_ });
	LureHitbox_->SetPivot({ Pivot_.x + 106.0f,  Pivot_.y + LurePosY_ });

	LurePosY_ += LureMoveDirY_;

	if (LurePosY_ <= -180.0f)
	{
		LurePosY_ = -170.0f;
	}
	else if (LurePosY_ >= 180.0f)
	{
		LurePosY_ = 170.0f;
	}

	if (this->GetAccTime() >= 0.1f)
	{
		LureTimeCount_++;
	}

	if (LureTimeCount_ >= 10)
	{
		int State = Random_->RandomInt(0, 7);

		if (State >= 0 && State <= 2)
		{
			LureCurState_ = LureState::MoveUp;
		}
		else if (State >= 3 && State <= 5)
		{
			LureCurState_ = LureState::MoveDown;
		}
		else
		{
			LureCurState_ = LureState::Idle;
		}

		LureTimeCount_ = 0;

		// 루어의 상태변경
		LureStateChange(LureCurState_);
	}
}

void FishingBar::LureStateChange(LureState _State)
{
	switch (_State)
	{
	case LureState::Idle:
		LureMoveDirY_ = 0.0f;
		break;
	case LureState::MoveUp:
		LureMoveDirY_ = -1.5f;
		break;
	case LureState::MoveDown:
		LureMoveDirY_ = 1.5f;
		break;
	default:
		LureMoveDirY_ = 0.0f;
		break;
	}
}