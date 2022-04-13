#pragma once
enum class ORDER
{
	COLLISION,
	BACKGROUND,		// ���
	BUIDING,		// ���
	FRONTA,			// �÷��̾��� �ڿ� �������� ����� Front��� (Default)
	PLAYER,
	FRONTB,			// �÷��̾ ���� ����� Front ���
	MONSTER,
	ALWAYSFRONT,	// ���
	UI,
	UIICONS,		// UI���� ������ ������, ���ڵ�
	UIMOUSE,		// ���콺 ������ (�ֻ���)	
}; 

enum class PlayerState
{
	Idle,
	Action,
	Move,
	Max,
};