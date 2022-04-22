#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Item.h"

// ���� :
class Crops : public GameEngineActor
{
public:
	// constrcuter destructer
	Crops();
	~Crops();

	// delete Function
	Crops(const Crops& _Other) = delete;
	Crops(Crops&& _Other) noexcept = delete;
	Crops& operator=(const Crops& _Other) = delete;
	Crops& operator=(Crops&& _Other) noexcept = delete;

	inline void SetHp(int _Hp)
	{
		Hp_ = _Hp;
	}

	inline int GetHp() const
	{
		return Hp_;
	}

	inline void SetGrowLevel(int _Level)
	{
		Level_ = _Level;
	}

	inline int GetGrowLevel() const
	{
		return Level_;
	}

	inline void SetMaxLevel(int _MaxLevel)
	{
		MaxLevel_ = _MaxLevel;
	}

	inline int GetMaxLevel() const
	{
		return MaxLevel_;
	}

	inline void SetIsTimeUpdate(bool _Flg)
	{
		IsTimeUpdate_ = _Flg;
	}

	inline bool GetIsTimeUpdate()
	{
		return IsTimeUpdate_;
	}

	inline void SetRenderer(GameEngineRenderer* _Renderer)
	{
		Renderer_ = _Renderer;
	}

	inline GameEngineRenderer* GetRenderer()
	{
		return Renderer_;
	}

	inline GameEngineActor* GetColActor()
	{
		return CollisionActor_;
	}

	inline int GetCropsRenderIndex()
	{
		return RenderCropsIndex_;
	}

	inline void SetCropsRenderIndex(int _Index)
	{
		RenderCropsIndex_ = _Index;
	}

	void Destroy();
	virtual Item* CreateItem() { return nullptr;  };

protected:
	void Start() override {};

	// Hp�� �ִ� �������� ���
	int Hp_ = 0;
	// ������� ��ȭ�� �ִ� ���
	int Level_ = 0;
	// ������ �ִ�ġ
	int MaxLevel_ = 0;
	// �̹��������� �ε���
	int RenderCropsIndex_ = 0;

	GameEngineRenderer* Renderer_;

	// �ð� ������ üũ�ϱ� ���� �÷���
	// false�� ��� �ð��� �ʱ�ȭ
	bool IsTimeUpdate_;

	// �浹ó���� ���� ����
	GameEngineActor* CollisionActor_;

	GameEngineRandom* RandomItem_;
private:


};

