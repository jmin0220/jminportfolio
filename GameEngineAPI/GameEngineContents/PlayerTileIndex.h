#pragma once
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>

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

	inline int GetIndexInfo() const
	{
		return IndexInfo_;
	}
	inline void SetIndexInfo(int _IndexInfo)
	{
		IndexInfo_ = _IndexInfo;
	}

private:
	// 타일에 무엇이 있는지
	int TileState_;
	int IndexInfo_;
};