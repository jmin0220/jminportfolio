#pragma once
#include "Item.h"

// Ό³Έν :
class BeetFruit : public Item
{
public:
	// constrcuter destructer
	BeetFruit();
	~BeetFruit();

	// delete Function
	BeetFruit(const BeetFruit& _Other) = delete;
	BeetFruit(BeetFruit&& _Other) noexcept = delete;
	BeetFruit& operator=(const BeetFruit& _Other) = delete;
	BeetFruit& operator=(BeetFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

