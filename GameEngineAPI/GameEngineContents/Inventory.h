#pragma once
#include "Item.h"
#include "Font.h"
#include <string>
#include <cstring>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

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
	int AddItemToInventory(int _ItemNum);

	inline std::string GetSelectedItemName()
	{
		return SelectedItemName_;
	}

	inline int GetSelectedItemNum()
	{
		return SelectedItemNumber_;
	}

	inline Item** GetInventoryList()
	{
		return InventoryList_;
	}

	inline void SetInventoryList(Item** _InventoryList)
	{
		memcpy(InventoryList_, _InventoryList, 36);
	}

	inline bool GetExtendFlg() const
	{
		return ExtendFlg_;
	}

	inline GameEngineCollision** GetInventoryNormalCol()
	{
		return ColInventoryNormalBox_;
	}

	inline GameEngineCollision** GetInventoryExtendCol()
	{
		return ColInventoryExtendBox_;
	}

	void DeleteItem(int i);

	void SelectItem(int i);
	Item* SwapItem_;
	void SwapItem(int _Origin, int _Target);

	void InventoryUpload();
	void InventoryDownload();

	void FontDeath();

protected:
	void Start() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	static char SelectBoxHotkey_;
	static std::string SelectedItemName_;
	static int SelectedItemNumber_;
	static float4 Pos_;
	static bool ExtendFlg_;
	static Item* InventorySaver_[36];

	// 인벤토리 UI
	GameEngineRenderer* RendererInven_;
	// 선택된 아이템 가이드박스
	GameEngineRenderer* RendererSelectBox_;

	void InitKey();

	void ControlSelectBox();
	void ExtendInventoryOn();
	// 아이템의 위치 계산
	void ItemPosCalc();

private:
	// 저장되어있는 아이템의 정보
	Item* InventoryList_[36];


	// 충돌관련
public:
	
private:
	void CollisionInit();

	// 인벤토리 UI관련 충돌처리
	GameEngineCollision* ColInventoryBar_;
	GameEngineCollision* ColInventoryExtBar_;
	// 인벤토리 1칸에 대한 충돌처리
	GameEngineCollision* ColInventoryNormalBox_[12];
	GameEngineCollision* ColInventoryExtendBox_[36];

};

