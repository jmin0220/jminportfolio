#pragma once
#include "Item.h"

// Ό³Έν :
class RhubarbFruit : public Item
{
public:
	// constrcuter destructer
	RhubarbFruit();
	~RhubarbFruit();

	// delete Function
	RhubarbFruit(const RhubarbFruit& _Other) = delete;
	RhubarbFruit(RhubarbFruit&& _Other) noexcept = delete;
	RhubarbFruit& operator=(const RhubarbFruit& _Other) = delete;
	RhubarbFruit& operator=(RhubarbFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

