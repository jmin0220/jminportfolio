#pragma once
#include "Item.h"

// Ό³Έν :
class SunflowerFruit : public Item
{
public:
	// constrcuter destructer
	SunflowerFruit();
	~SunflowerFruit();

	// delete Function
	SunflowerFruit(const SunflowerFruit& _Other) = delete;
	SunflowerFruit(SunflowerFruit&& _Other) noexcept = delete;
	SunflowerFruit& operator=(const SunflowerFruit& _Other) = delete;
	SunflowerFruit& operator=(SunflowerFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

