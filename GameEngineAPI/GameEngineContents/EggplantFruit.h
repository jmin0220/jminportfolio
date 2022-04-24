#pragma once
#include "Item.h"

// Ό³Έν :
class EggplantFruit : public Item
{
public:
	// constrcuter destructer
	EggplantFruit();
	~EggplantFruit();

	// delete Function
	EggplantFruit(const EggplantFruit& _Other) = delete;
	EggplantFruit(EggplantFruit&& _Other) noexcept = delete;
	EggplantFruit& operator=(const EggplantFruit& _Other) = delete;
	EggplantFruit& operator=(EggplantFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

