#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	// Player�� ��ġ�� ũ��
	SetPosition({ 688, 352 });
	CreateRenderer("player.bmp");

	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');

		// ��Ŭ���������� ��ȣ�ۿ�
		GameEngineInput::GetInst()->CreateKey("Interact", VK_LBUTTON);
	}
}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		SetMove(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		SetMove(float4::RIGHT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		SetMove(float4::UP);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		SetMove(float4::DOWN);
	}
}

//void Player::Render()
//{
//	// DebugRectRender();
//
//	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
//
//	if (nullptr == FindImage)
//	{
//		MsgBoxAssert("�̹��� �ε� ����");
//	}
//
//	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
//}