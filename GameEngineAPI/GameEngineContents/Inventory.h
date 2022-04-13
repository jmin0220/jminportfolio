#pragma once
#include "Item.h"
#include <string>
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Inventory : public GameEngineActor
{
public:
	// constrcuter destructer
	Inventory();
	~Inventory();

	// delete Function
	Inventory(const Inventory& _Other) = delete;
	Inventory(Inventory&& _Other) noexcept = delete;
	Inventory& operator=(const Inventory& _Other) = delete;
	Inventory& operator=(Inventory&& _Other) noexcept = delete;

	void SetPos(float4 _Pos);
	void AddItemToInventory(Item& _item);

	inline std::string GetSelectedItem()
	{
		return SelectedItem_;
	}

protected:
	void Start() override;
	void Update() override;

private:
	static char SelectBoxHotkey_;
	static std::string SelectedItem_;
	static float4 Pos_;
	static bool ExtendFlg;

	GameEngineRenderer* RendererInven_;
	GameEngineRenderer* RendererSelectBox_;

	void InitKey();

	void ControlSelectBox();
	void ExtendInventoryOn();

private:
	static Item* InventoryList_[36];
};

