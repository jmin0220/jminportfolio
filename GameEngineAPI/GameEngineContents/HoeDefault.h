#pragma once
#include "Tool.h"

// Ό³Έν :
class HoeDefault : public Tool
{
public:
	// constrcuter destructer
	HoeDefault();
	~HoeDefault();

	// delete Function
	HoeDefault(const HoeDefault& _Other) = delete;
	HoeDefault(HoeDefault&& _Other) noexcept = delete;
	HoeDefault& operator=(const HoeDefault& _Other) = delete;
	HoeDefault& operator=(HoeDefault&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update() override;

};

