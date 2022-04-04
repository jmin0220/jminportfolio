#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// 배경
	BUIDING,		// 배경
	PLAYER,
	MONSTER,
	FRONT,			// 배경
	ALWAYSFRONT,	// 배경
	UI
}; 

enum PlayerState
{
	Idle,
	Action,
	Move,
	Max,
};