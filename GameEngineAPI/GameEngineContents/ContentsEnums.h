#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// 배경
	BUIDING,		// 배경
	FRONT,			// 배경
	PLAYER,
	MONSTER,
	ALWAYSFRONT,	// 배경
	UI
}; 

enum class PlayerState
{
	Idle,
	Action,
	Move,
	Max,
};