#pragma once
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

	GameEngineRenderer& GetIconRenderer()
	{
		return *IconRenderer_;
	}

	void SetIconRenderer(GameEngineRenderer& _IconRenderer)
	{
		IconRenderer_ = &_IconRenderer;
	};
	
protected:
	// �������� �ʵ忡�� ���϶� �̹���
	GameEngineRenderer* ItemRenderer_;
	// �������� �κ��丮�� ���������� ������ �̹���
	GameEngineRenderer* IconRenderer_;


private:
	void Start() override;
};

