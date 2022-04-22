#pragma once
#include "Crops.h"

// Ό³Έν :
class Starfruit : public Crops
{
public:
	// constrcuter destructer
	Starfruit();
	~Starfruit();

	// delete Function
	Starfruit(const Starfruit& _Other) = delete;
	Starfruit(Starfruit&& _Other) noexcept = delete;
	Starfruit& operator=(const Starfruit& _Other) = delete;
	Starfruit& operator=(Starfruit&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

