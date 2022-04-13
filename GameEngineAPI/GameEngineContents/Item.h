#pragma once
#include <string>
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

	GameEngineRenderer& GetIconRenderer()
	{
		return *IconRenderer_;
	}

	void SetIconRenderer(GameEngineRenderer& _IconRenderer)
	{
		IconRenderer_ = &_IconRenderer;
	};

	GameEngineRenderer& GetItemRenderer()
	{
		return *ItemRenderer_;
	}
	
	std::string GetItenName() const
	{
		return ItemName_;
	}

protected:
	// 아이템이 필드에서 보일때 이미지
	GameEngineRenderer* ItemRenderer_;
	// 아이템이 인벤토리에 들어가있을때의 아이콘 이미지
	GameEngineRenderer* IconRenderer_;

	std::string ItemName_;

	// 장비가능한 아이템인가
	bool IsEuipment;

	// 중첩되는 아이템의 경우 갯수 세기
	int ItemCount_;

private:
	void Start() override;
};

