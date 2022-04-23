#pragma once
#include <string>
#include "Font.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

// 설명 :
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

	void AddCounter();

	void SetItemNum();

	bool ClickedFlg;
	Font* Font_[2];

	// 겹쳐질 수 있는 아이템인가
	bool Countable;
	// 얼마나 겹쳐져있는가
	std::string Counter_;

protected:
	// 아이템이 필드에서 보일때 이미지
	GameEngineRenderer* ItemRenderer_;
	// 아이템이 인벤토리에 들어가있을때의 아이콘 이미지
	GameEngineRenderer* IconRenderer_;


	std::string ItemName_;
	int IndexNum_;

private:
	void Start() override;
};

