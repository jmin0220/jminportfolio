#pragma once
#include "Crops.h"

// Ό³Έν :
class Pumpkin : public Crops
{
public:
	// constrcuter destructer
	Pumpkin();
	~Pumpkin();

	// delete Function
	Pumpkin(const Pumpkin& _Other) = delete;
	Pumpkin(Pumpkin&& _Other) noexcept = delete;
	Pumpkin& operator=(const Pumpkin& _Other) = delete;
	Pumpkin& operator=(Pumpkin&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

