#include "InventoryBar.h"

// �κ��丮�� �̷��� ����°� �ƴѵ�
InventoryBar::InventoryBar() 
{
}

InventoryBar::~InventoryBar() 
{
}

void InventoryBar::Start()
{
	// InventoryBar�������̽�������
	// ���
	SetPosition({ 640, 55 });
	//�ϴ�
	//SetPosition({ 640, 663 });
	CreateRenderer("InventoryBar.bmp");
}