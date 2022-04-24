#pragma once
#include "Item.h"

// Ό³Έν :
class GreenbeanFruit : public Item
{
public:
	// constrcuter destructer
	GreenbeanFruit();
	~GreenbeanFruit();

	// delete Function
	GreenbeanFruit(const GreenbeanFruit& _Other) = delete;
	GreenbeanFruit(GreenbeanFruit&& _Other) noexcept = delete;
	GreenbeanFruit& operator=(const GreenbeanFruit& _Other) = delete;
	GreenbeanFruit& operator=(GreenbeanFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

