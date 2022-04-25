#include "FishingPowerbar.h"
#include "ContentsEnums.h"
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

bool FishingPowerbar::GameUpdate()
{
	bool EndFlg = false;

	if (true == GameEngineInput::GetInst()->IsPress(KEY_INTERACT))
	{
		// ����
		if (PowerlevelDir_ == 0)
		{
			Powerlevel_++;

			if (Powerlevel_ >= 100)
			{
				PowerlevelDir_ = 1;
			}
		}
		// ����
		else if (PowerlevelDir_ == 1)
		{
			Powerlevel_--;

			if (Powerlevel_ >= 100)
			{
				PowerlevelDir_ = 0;
			}
		}
	}

	// ���콺�� ������� ������2�� �Ѿ
	if (true == GameEngineInput::GetInst()->IsUp(KEY_INTERACT))
	{
		EndFlg = true;
	}

	return EndFlg;
}