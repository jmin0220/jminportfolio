#pragma once
#include <string>
#include <GameEngineBase/GameEngineCustomStringSet.h>
#include <GameEngineBase/GameEngineString.h>


enum class ITEMTABLE
{
	// �������
	EMPTY,
	// ���
	HOE,			
	AXE,
	WATERINGCAN,
	// ����
	OAKTREE,
	MAPLETREE,
	PINETREE,
	// ����
	PARSNIP,
	POTATO,
	CORN,
	// �����
	PUFFERFISH,
	TUNA,
	ANCHOVY,
	// ������
	MINITREE,
};

// �������� �κ��丮�� �߰��Ҷ� ���ڿ��� �� �������� enum���� ��ȯ�Ͽ� ����
int StringtoItemTable(std::string _Name);