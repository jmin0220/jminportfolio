#pragma once
#include <GameEngine/GameEngineRendererTileMap.h>

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
private:
	// 타일에 무엇이 있는지
	int TileState_;

	// Hp가 있는 아이템의 경우
	int Hp_ = 0;
	// 성장등의 변화가 있는 경우
	int Level_ = 0;
};