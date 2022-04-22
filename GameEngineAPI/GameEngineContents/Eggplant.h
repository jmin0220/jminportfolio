#pragma once
#include "Crops.h"

// Ό³Έν :
class Eggplant : public Crops
{
public:
	// constrcuter destructer
	Eggplant();
	~Eggplant();

	// delete Function
	Eggplant(const Eggplant& _Other) = delete;
	Eggplant(Eggplant&& _Other) noexcept = delete;
	Eggplant& operator=(const Eggplant& _Other) = delete;
	Eggplant& operator=(Eggplant&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

