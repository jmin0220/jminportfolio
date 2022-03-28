#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();

GameEngineTime::GameEngineTime() 
{
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));

	// 현재 PC의 초당 성능 카운터 빈도를 SecondCount_에 저장
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));
	Update();
}

void GameEngineTime::Update()
{
	// 현재의 성능 카운터값을 CurrentCount_에 저장
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));

	// (현재 카운터 값 - 직전 카운터값) / 현재PC의 초당카운터 빈도
	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_)) / static_cast<double>(SecondCount_);

	// 다음 프레임 계산을 위해 현재 카운터값을 PrevCount_에 저장
	PrevCount_ = CurrentCount_;

	// double => float형으로 변환.
	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}