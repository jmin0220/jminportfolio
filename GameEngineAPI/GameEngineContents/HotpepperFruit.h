#pragma once
#include "Item.h"

// Ό³Έν :
class HotpepperFruit : public Item
{
public:
	// constrcuter destructer
	HotpepperFruit();
	~HotpepperFruit();

	// delete Function
	HotpepperFruit(const HotpepperFruit& _Other) = delete;
	HotpepperFruit(HotpepperFruit&& _Other) noexcept = delete;
	HotpepperFruit& operator=(const HotpepperFruit& _Other) = delete;
	HotpepperFruit& operator=(HotpepperFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

