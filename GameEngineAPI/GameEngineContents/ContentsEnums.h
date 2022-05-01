#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// ���
	BUIDING,		// ���
	FRONTA,			// �÷��̾��� �ڿ� �������� ����� Front��� (Default)
	PLAYER,
	FRONTB,			// �÷��̾ ���� ����� Front ���
	ALWAYSFRONT,	// ���
	UI,
	UIICONS,		// UI���� ������ ������
	UIFONT,			// ����
	FISHINGUI,
	FISHINGICONS,
	FISHINGLURE,
	SEEDSHOP_INTERFACE,
	SEEDSHOP_ICONS,
	SEEDSHOP_FONT,
	UIMOUSE,		// ���콺 ������ (�ֻ���)	
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