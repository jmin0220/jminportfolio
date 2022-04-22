#pragma once
#include "Crops.h"

// Ό³Έν :
class Yam : public Crops
{
public:
	// constrcuter destructer
	Yam();
	~Yam();

	// delete Function
	Yam(const Yam& _Other) = delete;
	Yam(Yam&& _Other) noexcept = delete;
	Yam& operator=(const Yam& _Other) = delete;
	Yam& operator=(Yam&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

