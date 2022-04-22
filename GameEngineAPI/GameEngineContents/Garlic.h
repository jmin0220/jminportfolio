#pragma once
#include "Crops.h"

// Ό³Έν :
class Garlic : public Crops
{
public:
	// constrcuter destructer
	Garlic();
	~Garlic();

	// delete Function
	Garlic(const Garlic& _Other) = delete;
	Garlic(Garlic&& _Other) noexcept = delete;
	Garlic& operator=(const Garlic& _Other) = delete;
	Garlic& operator=(Garlic&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

