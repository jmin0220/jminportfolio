#include "FishingPowerbar.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>

FishingPowerbar::FishingPowerbar() 
	: Powerlevel_(0)
	, PowerlevelDir_(0)
{
}

FishingPowerbar::~FishingPowerbar() 
{
}

void FishingPowerbar::Start()
{
	BarRenderer_ = CreateRenderer(IMAGE_FISHING_POWERBAR, (int)ORDER::UI);
	BarRenderer_->Off();
}

void FishingPowerbar::GameStart()
{
	float4 Pivot = static_cast<Player*>(this->GetLevel()->FindActor(ACTOR_PLAYER))->GetPosition();
	BarRenderer_->SetPivot({ Pivot.x, Pivot.y - 100.0f });
	BarRenderer_->On();
}

void FishingPowerbar::GameEnd()
{
	BarRenderer_->Off();
}

bool FishingPowerbar::GameUpdate()
{
	bool EndFlg = false;

	if (true == GameEngineInput::GetInst()->IsPress(KEY_INTERACT))
	{
		// 증가
		if (PowerlevelDir_ == 0)
		{
			Powerlevel_++;

			if (Powerlevel_ >= 100)
			{
				PowerlevelDir_ = 1;
			}
		}
		// 감소
		else if (PowerlevelDir_ == 1)
		{
			Powerlevel_--;

			if (Powerlevel_ >= 100)
			{
				PowerlevelDir_ = 0;
			}
		}
	}

	// 마우스를 뗐을경우 페이즈2로 넘어감
	if (true == GameEngineInput::GetInst()->IsUp(KEY_INTERACT))
	{
		EndFlg = true;
	}

	return EndFlg;
}