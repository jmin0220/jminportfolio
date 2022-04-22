#pragma once
#include "Crops.h"

// Ό³Έν :
class Radish : public Crops
{
public:
	// constrcuter destructer
	Radish();
	~Radish();

	// delete Function
	Radish(const Radish& _Other) = delete;
	Radish(Radish&& _Other) noexcept = delete;
	Radish& operator=(const Radish& _Other) = delete;
	Radish& operator=(Radish&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

