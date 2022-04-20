#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// 설명 :
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

	inline void SetCropState(int _CropState)
	{
		CropState_ = _CropState;
	}

	inline int GetCropState()
	{
		return CropState_;
	}

protected:
	void Start() override {};

	// Hp가 있는 아이템의 경우
	int Hp_ = 0;
	// 성장등의 변화가 있는 경우
	int Level_ = 0;
	// 성장의 최대치
	int MaxLevel_ = 0;
	// 농작물의 종류
	int CropState_;

	GameEngineRenderer* Renderer_;

	// 시간 갱신을 체크하기 위한 플래그
	// false일 경우 시간을 초기화
	bool IsTimeUpdate_;

	// 충돌처리를 위한 액터
	GameEngineActor* CollisionActor_;
private:


};

