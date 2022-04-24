#pragma once
#include "Item.h"

// Ό³Έν :
class RadishFruit : public Item
{
public:
	// constrcuter destructer
	RadishFruit();
	~RadishFruit();

	// delete Function
	RadishFruit(const RadishFruit& _Other) = delete;
	RadishFruit(RadishFruit&& _Other) noexcept = delete;
	RadishFruit& operator=(const RadishFruit& _Other) = delete;
	RadishFruit& operator=(RadishFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

