#pragma once
#include <GameEngine/GameEngineRendererTileMap.h>

class PlayerTileIndex : public Tile
{
public:
	inline void SetTileState_(int _TileState)
	{
		TileState_ = _TileState;
	}

	inline int GetTileState() const
	{
		return TileState_;
	}
private:
	int TileState_;
};