#pragma once
#include "Crops.h"

// Ό³Έν :
class Redcabbage : public Crops
{
public:
	// constrcuter destructer
	Redcabbage();
	~Redcabbage();

	// delete Function
	Redcabbage(const Redcabbage& _Other) = delete;
	Redcabbage(Redcabbage&& _Other) noexcept = delete;
	Redcabbage& operator=(const Redcabbage& _Other) = delete;
	Redcabbage& operator=(Redcabbage&& _Other) noexcept = delete;

	Item* CreateItem() override;
protected:
	void Start() override;

private:

};

