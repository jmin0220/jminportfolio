#pragma once
#include "Crops.h"

// Ό³Έν :
class Couliflower : public Crops
{
public:
	// constrcuter destructer
	Couliflower();
	~Couliflower();

	// delete Function
	Couliflower(const Couliflower& _Other) = delete;
	Couliflower(Couliflower&& _Other) noexcept = delete;
	Couliflower& operator=(const Couliflower& _Other) = delete;
	Couliflower& operator=(Couliflower&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

