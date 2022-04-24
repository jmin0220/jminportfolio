#pragma once
#include "Item.h"

// Ό³Έν :
class StarfruitFruit : public Item
{
public:
	// constrcuter destructer
	StarfruitFruit();
	~StarfruitFruit();

	// delete Function
	StarfruitFruit(const StarfruitFruit& _Other) = delete;
	StarfruitFruit(StarfruitFruit&& _Other) noexcept = delete;
	StarfruitFruit& operator=(const StarfruitFruit& _Other) = delete;
	StarfruitFruit& operator=(StarfruitFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

