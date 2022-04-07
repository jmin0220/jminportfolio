#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// 배경
	BUIDING,		// 배경
	FRONTA,			// 플레이어의 뒤에 렌더링될 경우의 Front배경 (Default)
	PLAYER,
	FRONTB,			// 플레이어를 가릴 경우의 Front 배경
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