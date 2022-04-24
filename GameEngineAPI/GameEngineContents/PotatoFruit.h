#pragma once
#include "Item.h"

// Ό³Έν :
class PotatoFruit : public Item
{
public:
	// constrcuter destructer
	PotatoFruit();
	~PotatoFruit();

	// delete Function
	PotatoFruit(const PotatoFruit& _Other) = delete;
	PotatoFruit(PotatoFruit&& _Other) noexcept = delete;
	PotatoFruit& operator=(const PotatoFruit& _Other) = delete;
	PotatoFruit& operator=(PotatoFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

