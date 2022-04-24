#pragma once
#include "Item.h"

// Ό³Έν :
class GarlicFruit : public Item
{
public:
	// constrcuter destructer
	GarlicFruit();
	~GarlicFruit();

	// delete Function
	GarlicFruit(const GarlicFruit& _Other) = delete;
	GarlicFruit(GarlicFruit&& _Other) noexcept = delete;
	GarlicFruit& operator=(const GarlicFruit& _Other) = delete;
	GarlicFruit& operator=(GarlicFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

