#pragma once
#include "Item.h"

// Ό³Έν :
class RedcabbageFruit : public Item
{
public:
	// constrcuter destructer
	RedcabbageFruit();
	~RedcabbageFruit();

	// delete Function
	RedcabbageFruit(const RedcabbageFruit& _Other) = delete;
	RedcabbageFruit(RedcabbageFruit&& _Other) noexcept = delete;
	RedcabbageFruit& operator=(const RedcabbageFruit& _Other) = delete;
	RedcabbageFruit& operator=(RedcabbageFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

