#pragma once
#include "Tool.h"

// Ό³Έν :
class HoeBasic : public Tool
{
public:
	// constrcuter destructer
	HoeBasic();
	~HoeBasic();

	// delete Function
	HoeBasic(const HoeBasic& _Other) = delete;
	HoeBasic(HoeBasic&& _Other) noexcept = delete;
	HoeBasic& operator=(const HoeBasic& _Other) = delete;
	HoeBasic& operator=(HoeBasic&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

};

