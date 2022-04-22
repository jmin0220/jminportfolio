#pragma once
#include "Crops.h"

// Ό³Έν :
class Sunflower : public Crops
{
public:
	// constrcuter destructer
	Sunflower();
	~Sunflower();

	// delete Function
	Sunflower(const Sunflower& _Other) = delete;
	Sunflower(Sunflower&& _Other) noexcept = delete;
	Sunflower& operator=(const Sunflower& _Other) = delete;
	Sunflower& operator=(Sunflower&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

