#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// ���
	BUIDING,		// ���
	FRONT,			// ���
	PLAYER,
	MONSTER,
	ALWAYSFRONT,	// ���
	UI
}; 

enum class PlayerState
{
	Idle,
	Action,
	Move,
	Max,
};