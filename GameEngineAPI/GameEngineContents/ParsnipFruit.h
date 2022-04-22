#pragma once
#include "Item.h"

// Ό³Έν :
class ParsnipFruit : public Item
{
public:
	// constrcuter destructer
	ParsnipFruit();
	~ParsnipFruit();

	// delete Function
	ParsnipFruit(const ParsnipFruit& _Other) = delete;
	ParsnipFruit(ParsnipFruit&& _Other) noexcept = delete;
	ParsnipFruit& operator=(const ParsnipFruit& _Other) = delete;
	ParsnipFruit& operator=(ParsnipFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

