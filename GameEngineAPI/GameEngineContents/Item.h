#pragma once
#include <string>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

// ���� :
class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	virtual ~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

	void SetIconRendererInfo(int _ItemNum);

	inline void SetIconRenderer(GameEngineRenderer& _IconRenderer)
	{
		IconRenderer_ = &_IconRenderer;
	};

	inline void SetItemRenderer(GameEngineRenderer& _ItemRenderer)
	{
		ItemRenderer_ = &_ItemRenderer;
	};

	inline GameEngineRenderer& GetIconRenderer()
	{
		return *IconRenderer_;
	}

	inline GameEngineRenderer& GetItemRenderer()
	{
		return *ItemRenderer_;
	}
	
	inline std::string GetItemName() const
	{
		return ItemName_;
	}

	inline void SetItemName(std::string _Name)
	{
		ItemName_ = _Name;
	}

	inline int GetIndexNum()
	{
		return IndexNum_;
	}

	inline void SetIndexNum(int _IndexNum)
	{
		IndexNum_ = _IndexNum;
	}

protected:
	// �������� �ʵ忡�� ���϶� �̹���
	GameEngineRenderer* ItemRenderer_;
	// �������� �κ��丮�� ���������� ������ �̹���
	GameEngineRenderer* IconRenderer_;

	std::string ItemName_;
	int IndexNum_;

private:
	void Start() override;
};

