#pragma once
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>

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

	// 매 프레임 업데이트
	inline void AddAccTime()
	{
		AccTime_ += GameEngineTime::GetDeltaTime();
	}

	inline float GetAccTime()
	{
		return AccTime_;
	}

	// 시간 초기화
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

private:
	// 타일에 무엇이 있는지
	int TileState_;

	// Hp가 있는 아이템의 경우
	int Hp_ = 0;
	// 성장등의 변화가 있는 경우
	int Level_ = 0;
	// 성장의 최대치
	int MaxLevel_ = 0;

	// 시간체크
	float AccTime_;
	bool IsTimeUpdate_ = false;

	// GrounTiles <-> EnvironmentTiles의 상태를 확인하기 위해 자신의 위치 정보를 가지고 있기
	float4 Pos_;
};