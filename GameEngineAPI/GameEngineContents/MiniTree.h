#pragma once
#include "Item.h"

// Ό³Έν :
class MiniTree : public Item
{
public:
	// constrcuter destructer
	MiniTree();
	~MiniTree();

	// delete Function
	MiniTree(const MiniTree& _Other) = delete;
	MiniTree(MiniTree&& _Other) noexcept = delete;
	MiniTree& operator=(const MiniTree& _Other) = delete;
	MiniTree& operator=(MiniTree&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

