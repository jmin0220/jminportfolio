#pragma once
#include "Item.h"

// Ό³Έν :
class BlueberryFruit : public Item
{
public:
	// constrcuter destructer
	BlueberryFruit();
	~BlueberryFruit();

	// delete Function
	BlueberryFruit(const BlueberryFruit& _Other) = delete;
	BlueberryFruit(BlueberryFruit&& _Other) noexcept = delete;
	BlueberryFruit& operator=(const BlueberryFruit& _Other) = delete;
	BlueberryFruit& operator=(BlueberryFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

