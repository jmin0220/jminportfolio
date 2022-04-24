#pragma once
#include "Item.h"

// Ό³Έν :
class MelonFruit : public Item
{
public:
	// constrcuter destructer
	MelonFruit();
	~MelonFruit();

	// delete Function
	MelonFruit(const MelonFruit& _Other) = delete;
	MelonFruit(MelonFruit&& _Other) noexcept = delete;
	MelonFruit& operator=(const MelonFruit& _Other) = delete;
	MelonFruit& operator=(MelonFruit&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

