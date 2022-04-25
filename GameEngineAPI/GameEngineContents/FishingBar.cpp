#include "FishingBar.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>

FishingBar::FishingBar() 
	: SuccessFlg_(false)
	, ProgressLevel_(40)
	, HitboxSpeed_(0.0f)
{
}

FishingBar::~FishingBar() 
{
}

void FishingBar::Start()
{
	Renderer_ = CreateRenderer(IMAGE_FISHING_FISHINGBAR, (int)ORDER::UI);
	Renderer_->Off();

	ProgressRenderer_ = CreateRenderer(IMAGE_FISHING_PROGRESS, (int)ORDER::UIICONS);
	ProgressRenderer_->SetPivot({ 0.0f, 50.0f });
	ProgressRenderer_->Off();

	HitboxRenderer_ = CreateRenderer(IMAGE_FISHING_CATCH_HITBOX, (int)ORDER::UIICONS);
	HitboxRenderer_->SetPivot({ 0.0f, 100.0f });
	HitboxRenderer_->Off();

	FishHitbox_ = CreateCollision(COL_GROUP_FISH_HITBOX, { 30.0f, 30.0f });
	CatchHitbox_ = CreateCollision(COL_GROUP_CATCH_HITBOX, { 27.0f, 108.0f });
}

int FishingBar::GameUpdate()
{
	int EndFlg = 0;

	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		HitboxSpeed_ += 10.0f;
	}

	HitboxSpeed_ -= 5.0f;

	if (HitboxSpeed_ <= -20.0f)
	{
		HitboxSpeed_ = -20.0f;
	}

	HitboxRenderer_->SetPivot({ 0.0f, 0.0f });
	CatchHitbox_->SetPivot({ 0.0f, 0.0f });

	// 겹쳐지고 있으면 프로그레스바가 증가함
	if (true == CatchHitbox_->CollisionCheck(COL_GROUP_FISH_HITBOX, CollisionType::Rect, CollisionType::Rect))
	{
		ProgressLevel_++;
		ProgressRenderer_->SetIndex(ProgressLevel_-1);
	}
	else
	{
		ProgressLevel_--;
		ProgressRenderer_->SetIndex(ProgressLevel_-1);
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