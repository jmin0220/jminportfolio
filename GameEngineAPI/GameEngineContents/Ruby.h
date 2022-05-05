#pragma once
#include "Item.h"

// Ό³Έν :
class Ruby : public Item
{
public:
	// constrcuter destructer
	Ruby();
	~Ruby();

	// delete Function
	Ruby(const Ruby& _Other) = delete;
	Ruby(Ruby&& _Other) noexcept = delete;
	Ruby& operator=(const Ruby& _Other) = delete;
	Ruby& operator=(Ruby&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

