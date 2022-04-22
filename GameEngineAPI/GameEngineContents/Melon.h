#pragma once
#include "Crops.h"

// Ό³Έν :
class Melon : public Crops
{
public:
	// constrcuter destructer
	Melon();
	~Melon();

	// delete Function
	Melon(const Melon& _Other) = delete;
	Melon(Melon&& _Other) noexcept = delete;
	Melon& operator=(const Melon& _Other) = delete;
	Melon& operator=(Melon&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

