#pragma once
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

	GameEngineRenderer* GetIconRenderer()
	{
		return IconRenderer;
	}
	
protected:


private:
	// 아이템이 인벤토리에 들어가있을때의 아이콘 이미지
	GameEngineRenderer* IconRenderer;

	void SetIconRenderer(GameEngineRenderer& _IconRenderer)
	{
		IconRenderer = &_IconRenderer;
	};
};

