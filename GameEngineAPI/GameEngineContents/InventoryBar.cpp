#include "InventoryBar.h"
#include "Player.h"

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
	SetPosition({ IMAGE_INVENTORYBAR_POS_UP_W, IMAGE_INVENTORYBAR_POS_UP_H });
	//�ϴ�
	//SetPosition({ IMAGE_INVENTORYBAR_POS_DOWN_W, IMAGE_INVENTORYBAR_POS_DOWN_H });
	CreateRenderer("InventoryBar.bmp");
}