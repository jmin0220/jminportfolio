#pragma once
#include "Item.h"

// Ό³Έν :
class TomatoFruit : public Item
{
public:
	// constrcuter destructer
	TomatoFruit();
	~TomatoFruit();

	// delete Function
	TomatoFruit(const TomatoFruit& _Other) = delete;
	TomatoFruit(TomatoFruit&& _Other) noexcept = delete;
	TomatoFruit& operator=(const TomatoFruit& _Other) = delete;
	TomatoFruit& operator=(TomatoFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

