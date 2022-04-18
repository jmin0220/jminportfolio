#pragma once

enum class TILESTATE
{
	None,		// 파낼 수 있음
	Grass,		// 파낼 수 없음
	Hollow,		// 파여져있음
	HollowWet,	// 파여져있고 젖어있음
	Planted,	// 무언가 심겨져있음
	Axe,		// 도끼일때 상호작용
	// 나무
	OAKTREE,
	MAPLETREE,
	PINETREE,
	// 씨앗
	PARSNIP,
	POTATO,
	CORN,
};