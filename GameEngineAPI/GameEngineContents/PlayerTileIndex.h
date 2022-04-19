#pragma once
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>

class PlayerTileIndex : public Tile
{
public:
	inline void SetTileState(int _TileState)
	{
		TileState_ = _TileState;
	}

	inline int GetTileState() const
	{
		return TileState_;
	}

	inline void SetHp(int _Hp)
	{
		Hp_ = _Hp;
	}

	inline int GetHp() const
	{
		return Hp_;
	}

	inline void SetLevel(int _Level)
	{
		Level_ = _Level;
	}

	inline int GetLevel() const
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

	// �� ������ ������Ʈ
	inline void AddAccTime()
	{
		AccTime_ += GameEngineTime::GetDeltaTime();
	}

	inline float GetAccTime()
	{
		return AccTime_;
	}

	// �ð� �ʱ�ȭ
	inline void ReSetAccTime()
	{
		AccTime_ = 0.0f;
	}

	inline void SetIsTimeUpdate(bool _Flg)
	{
		IsTimeUpdate_ = _Flg;
	}

	inline bool GetIsTimeUpdate()
	{
		return IsTimeUpdate_;
	}

	inline void SetPos(float4 _Pos)
	{
		Pos_ = _Pos;
	}

	inline float4 GetPos()
	{
		return Pos_;
	}

	inline GameEngineCollision* GetCollision()
	{
		return Collision_;
	}

	inline void SetCollision(GameEngineCollision* _Collision)
	{
		Collision_ = _Collision;
	}

private:
	// Ÿ�Ͽ� ������ �ִ���
	int TileState_;

	// Hp�� �ִ� �������� ���
	int Hp_ = 0;
	// ������� ��ȭ�� �ִ� ���
	int Level_ = 0;
	// ������ �ִ�ġ
	int MaxLevel_ = 0;

	// �ð�üũ
	float AccTime_;
	bool IsTimeUpdate_ = false;

	// ���콺���� �浹ó��
	GameEngineCollision* Collision_;

	// GrounTiles <-> EnvironmentTiles�� ���¸� Ȯ���ϱ� ���� �ڽ��� ��ġ ������ ������ �ֱ�
	float4 Pos_;
};