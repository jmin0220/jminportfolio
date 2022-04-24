#pragma once
#include "Item.h"

// Ό³Έν :
class PumpkinFruit : public Item
{
public:
	// constrcuter destructer
	PumpkinFruit();
	~PumpkinFruit();

	// delete Function
	PumpkinFruit(const PumpkinFruit& _Other) = delete;
	PumpkinFruit(PumpkinFruit&& _Other) noexcept = delete;
	PumpkinFruit& operator=(const PumpkinFruit& _Other) = delete;
	PumpkinFruit& operator=(PumpkinFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

