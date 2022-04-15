#pragma once
#include "Item.h"
#include <string>
#include <cstring>
#include <GameEngine/GameEngineActor.h>

// 설명 :
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

	void InventoryInit();

	void SetPos(float4 _Pos);
	void AddItemToInventory(int _ItemNum);

	inline std::string GetSelectedItem()
	{
		return SelectedItem_;
	}

	inline Item** GetInventoryList()
	{
		return InventoryList_;
	}

	inline void SetInventoryList(Item** _InventoryList)
	{
		memcpy(InventoryList_, _InventoryList, 36);
	}

protected:
	void Start() override;
	void Update() override;
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	static char SelectBoxHotkey_;
	static std::string SelectedItem_;
	static float4 Pos_;
	static bool ExtendFlg;
	static Item* InventorySaver_[36];

	// 인벤토리 UI
	GameEngineRenderer* RendererInven_;
	// 선택된 아이템 가이드박스
	GameEngineRenderer* RendererSelectBox_;

	void InitKey();

	void ControlSelectBox();
	void ExtendInventoryOn();

private:
	// 저장되어있는 아이템의 정보
	Item* InventoryList_[36];

	inline void SelectItem(int i)
	{
		SelectBoxHotkey_ = i;
		SelectedItem_ = InventoryList_[i]->GetItemName();
	}
};

