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
	UIMOUSE,		// ���콺 ������ (�ֻ���)	
}; 

enum class PlayerState
{
	Idle,
	Action,
	Fishing,
	Move,
	Max,
};

enum class LureState
{
	Idle,
	MoveUp,
	MoveDown,
};