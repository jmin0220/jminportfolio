#pragma once
#include "Crops.h"

// Ό³Έν :
class Hotpepper : public Crops
{
public:
	// constrcuter destructer
	Hotpepper();
	~Hotpepper();

	// delete Function
	Hotpepper(const Hotpepper& _Other) = delete;
	Hotpepper(Hotpepper&& _Other) noexcept = delete;
	Hotpepper& operator=(const Hotpepper& _Other) = delete;
	Hotpepper& operator=(Hotpepper&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

