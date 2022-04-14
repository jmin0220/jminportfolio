#pragma once

enum class TILESTATE
{
	None,		// 파낼 수 있음
	Grass,		// 파낼 수 없음
	Hollow,		// 파여져있음
	HollowWet,	// 파여져있고 젖어있음
	Crops,		// 무언가 심겨져 있음
};