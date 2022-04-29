#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// 배경
	BUIDING,		// 배경
	FRONTA,			// 플레이어의 뒤에 렌더링될 경우의 Front배경 (Default)
	TOOLA,
	PLAYER,
	TOOLB,
	FRONTB,			// 플레이어를 가릴 경우의 Front 배경
	ALWAYSFRONT,	// 배경
	UI,
	UIICONS,		// UI위에 쓰여질 아이콘
	UIFONT,			// 글자
	FISHINGUI,
	FISHINGICONS,
	FISHINGLURE,
	SEEDSHOP_INTERFACE,
	SEEDSHOP_ICONS,
	SEEDSHOP_FONT,
	UIMOUSE,		// 마우스 포인터 (최상위)	
}; 

enum class PlayerState
{
	Idle,
	Action,
	Fishing,
	Move,
	Shop,
	Max,
};

enum class LureState
{
	Idle,
	MoveUp,
	MoveDown,
};