#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// ���
	BUIDING,		// ���
	PLAYER,
	MONSTER,
	FRONT,			// ���
	ALWAYSFRONT,	// ���
	UI
}; 

enum PlayerState
{
	Idle,
	Action,
	Move,
	Max,
};