#include "Mouse.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h> 

Mouse::Mouse() :
	CursorPos_({}),
	MousePoint_(nullptr)
{
}

Mouse::~Mouse() 
{
}

void Mouse::Start()
{
	CursorPos_ = { MAP_FARM_SIZE_H / 2, MAP_FARM_SIZE_W / 2 };
	MousePoint_ = CreateRenderer(IMAGE_MOUSE_CURSOR);
	MousePoint_->CameraEffectOff();


	MouseCollision_ = CreateCollision(COL_GROUP_MOUSE, { 12, 15}, { -12, -15 });

	// ��Ŭ���������� ��ȣ�ۿ�
	if (false == GameEngineInput::GetInst()->IsKey(KEY_INTERACT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_INTERACT, VK_LBUTTON);
	}
}

void Mouse::Update()
{
	ShowCursor(FALSE);
	GetCursorPos(&pt);

	// ScreenToClient ����� ȭ�鿡�� ������ ������ ȭ�� ��ǥ�� Ŭ���̾�Ʈ ���� ��ǥ�� ��ȯ�մϴ�.
	ScreenToClient(GameEngineWindow::GetHWND(), &pt);

	CursorPos_.x = static_cast<float>(pt.x);
	CursorPos_.y = static_cast<float>(pt.y);

	MousePoint_->GetActor()->SetPosition(CursorPos_);
}

void Mouse::Render()
{
}

bool Mouse::IsMouseDown()
{
	return (GameEngineInput::GetInst()->IsDown(KEY_INTERACT));
}

bool Mouse::IsMousePress()
{
	return (GameEngineInput::GetInst()->IsPress(KEY_INTERACT));
}

bool Mouse::IsMouseFree()
{
	return (GameEngineInput::GetInst()->IsUp(KEY_INTERACT));
}