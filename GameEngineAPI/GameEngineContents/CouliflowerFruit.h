#pragma once
#include "Item.h"

// Ό³Έν :
class CouliflowerFruit : public Item
{
public:
	// constrcuter destructer
	CouliflowerFruit();
	~CouliflowerFruit();

	// delete Function
	CouliflowerFruit(const CouliflowerFruit& _Other) = delete;
	CouliflowerFruit(CouliflowerFruit&& _Other) noexcept = delete;
	CouliflowerFruit& operator=(const CouliflowerFruit& _Other) = delete;
	CouliflowerFruit& operator=(CouliflowerFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

