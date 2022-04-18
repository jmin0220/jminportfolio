#pragma once

enum class TILESTATE
{
	NONE,		// 파낼 수 있음
	GRASS,		// 파낼 수 없음
	HOLLOW,		// 파여져있음
	HOLLOWWET,	// 파여져있고 젖어있음
	PLANTED,	// 무언가 심겨져있음
	AXE,		// 도끼일때 상호작용
	// 나무
	OAKTREE,
	MAPLETREE,
	PINETREE,
	// 씨앗
	PARSNIP,
	POTATO,
	CORN,
};