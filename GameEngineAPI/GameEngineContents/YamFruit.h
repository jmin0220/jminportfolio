#pragma once
#include "Item.h"

// Ό³Έν :
class YamFruit : public Item
{
public:
	// constrcuter destructer
	YamFruit();
	~YamFruit();

	// delete Function
	YamFruit(const YamFruit& _Other) = delete;
	YamFruit(YamFruit&& _Other) noexcept = delete;
	YamFruit& operator=(const YamFruit& _Other) = delete;
	YamFruit& operator=(YamFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

