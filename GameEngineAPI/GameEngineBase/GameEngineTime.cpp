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

	// ���� PC�� �ʴ� ���� ī���� �󵵸� SecondCount_�� ����
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));
	Update();
}

void GameEngineTime::Update()
{
	// ������ ���� ī���Ͱ��� CurrentCount_�� ����
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));

	// (���� ī���� �� - ���� ī���Ͱ�) / ����PC�� �ʴ�ī���� ��
	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_)) / static_cast<double>(SecondCount_);

	// ���� ������ ����� ���� ���� ī���Ͱ��� PrevCount_�� ����
	PrevCount_ = CurrentCount_;

	// double => float������ ��ȯ.
	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}