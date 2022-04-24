#pragma once
#include "Item.h"
#include "Font.h"
#include <string>
#include <cstring>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineCollision.h>

// ���� :
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

	// �κ��丮 UI
	GameEngineRenderer* RendererInven_;
	// ���õ� ������ ���̵�ڽ�
	GameEngineRenderer* RendererSelectBox_;

	void InitKey();

	void ControlSelectBox();
	void ExtendInventoryOn();
	// �������� ��ġ ���
	void ItemPosCalc();

private:
	// ����Ǿ��ִ� �������� ����
	Item* InventoryList_[36];


	// �浹����
public:
	
private:
	void CollisionInit();

	// �κ��丮 UI���� �浹ó��
	GameEngineCollision* ColInventoryBar_;
	GameEngineCollision* ColInventoryExtBar_;
	// �κ��丮 1ĭ�� ���� �浹ó��
	GameEngineCollision* ColInventoryNormalBox_[12];
	GameEngineCollision* ColInventoryExtendBox_[36];

};

