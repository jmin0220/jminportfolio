#include "Crops.h"

Crops::Crops() 
{
	RandomItem_ = new GameEngineRandom();
}

Crops::~Crops() 
{
	delete RandomItem_;
	RandomItem_ = nullptr;
}

void Crops::Destroy()
{
	this->Death();

	// 최대로 성장한 상태에서  파괴되었을 경우 아이템 생성
	// 그 외에는 그냥 파괴됨
	if (GetMaxLevel() == GetGrowLevel())
	{
		this->CreateItem();
	}
}