#pragma once
#include "Crops.h"

// Ό³Έν :
class Tomato : public Crops
{
public:
	// constrcuter destructer
	Tomato();
	~Tomato();

	// delete Function
	Tomato(const Tomato& _Other) = delete;
	Tomato(Tomato&& _Other) noexcept = delete;
	Tomato& operator=(const Tomato& _Other) = delete;
	Tomato& operator=(Tomato&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

