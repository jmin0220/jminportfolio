#include "Clock.h"
#include <math.h>
#include "ContentsEnums.h"
#include <GameEngine/GameEngineLevel.h>

Clock::Clock() 
{
}

Clock::~Clock() 
{
}

void Clock::Start()
{
	// Clock�������̽�������
	SetPosition({ IMAGE_CLOCK_POS_W, IMAGE_CLOCK_POS_H });
	GameEngineRenderer* Renderer = CreateRendererToScale("Clock.bmp", { IMAGE_CLOCK_SIZE_W, IMAGE_CLOCK_SIZE_H });
	Renderer->CameraEffectOff();

	for (size_t i = 0; i < 8; i++)
	{
		GoldFont_[i] = this->GetLevel()->CreateActor<Font>((int)ORDER::UIFONT);
	}
}

void Clock::SetGold(int _Num)
{
	for (size_t i = 8; i > 0; i--)
	{
		GoldFont_[i - 1]->GetNumberFont(_Num % 10);
		GoldFont_[i - 1]->SetPosition({ // IMAGE_CLOCK_POS_W - (144.0f + 48.0f * i)
									 IMAGE_CLOCK_POS_W - 91 + (24.0f * i)
			                       , IMAGE_CLOCK_POS_H + 92});

		_Num /= 10;
	}
}