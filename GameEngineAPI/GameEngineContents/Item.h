#pragma once
#include <string>
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

	void SetIconRendererImage(int _ItemNum);

	void SetIconRenderer(GameEngineRenderer& _IconRenderer)
	{
		IconRenderer_ = &_IconRenderer;
	};

	GameEngineRenderer& GetIconRenderer()
	{
		return *IconRenderer_;
	}

	GameEngineRenderer& GetItemRenderer()
	{
		return *ItemRenderer_;
	}
	
	std::string GetItemName() const
	{
		return ItemName_;
	}



protected:
	// �������� �ʵ忡�� ���϶� �̹���
	GameEngineRenderer* ItemRenderer_;
	// �������� �κ��丮�� ���������� ������ �̹���
	GameEngineRenderer* IconRenderer_;

	std::string ItemName_;

private:
	void Start() override;
};

