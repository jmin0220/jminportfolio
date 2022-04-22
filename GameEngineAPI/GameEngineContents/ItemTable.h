#pragma once
#include <string>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngineBase/GameEngineString.h>


enum class ITEMTABLE
{
	// 비어있음
	EMPTY,
	// 장비
	HOE,			
	AXE,
	WATERINGCAN,
	// 나무
	OAKTREE,
	MAPLETREE,
	PINETREE,
	// 씨앗
	PARSNIP,
	POTATO,
	CORN,
	// 물고기
	PUFFERFISH,
	TUNA,
	ANCHOVY,
	// 아이템
	MINITREE,
};

// 아이템을 인벤토리에 추가할때 문자열로 된 아이템을 enum으로 변환하여 리턴
int StringtoItemTable(std::string _Name);