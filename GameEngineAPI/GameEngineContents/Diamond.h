#pragma once
#include "Item.h"

// Ό³Έν :
class Diamond : public Item
{
public:
	// constrcuter destructer
	Diamond();
	~Diamond();

	// delete Function
	Diamond(const Diamond& _Other) = delete;
	Diamond(Diamond&& _Other) noexcept = delete;
	Diamond& operator=(const Diamond& _Other) = delete;
	Diamond& operator=(Diamond&& _Other) noexcept = delete;

protected:
	void Start() override;

private:

};

