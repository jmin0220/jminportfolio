#pragma once
#include "Tool.h"

// 설명 :
class WateringCan : public Tool
{
public:
	// constrcuter destructer
	WateringCan();
	~WateringCan();

	// delete Function
	WateringCan(const WateringCan& _Other) = delete;
	WateringCan(WateringCan&& _Other) noexcept = delete;
	WateringCan& operator=(const WateringCan& _Other) = delete;
	WateringCan& operator=(WateringCan&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

	// 남아있는 횟수
	// int RemainWater_;

};

