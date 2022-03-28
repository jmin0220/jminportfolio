#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>
#include "HoeDefault.h"

Player::Player() 
	:Speed_(100.0f)
	, Direction_(0)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	// Player�� ��ġ�� ũ��
	SetPosition(GameEngineWindow::GetScale().Half());
	//CreateRenderer("player.bmp");

	// �÷��̾� ĳ���� ������
	// ����
	GameEngineRenderer* Renderer;
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(Direction_);
	// ��
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(Direction_ + 6);
	// ����
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(Direction_ + 18);
	Renderer = CreateRenderer(IMAGE_PLAYER_HAIR);
	Renderer->SetIndex(Direction_);
	//Renderer = CreateRenderer(IMAGE_PLAYER_CLOTH);
	//Renderer->SetIndex(Direction_);
	//Renderer = CreateRenderer(IMAGE_PLAYER_HAT);
	//Renderer->SetIndex(Direction_);
	//Renderer = CreateRenderer(IMAGE_PLAYER_MASK);
	//Renderer->SetIndex(Direction_);

	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOVE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_LEFT, 'A');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_RIGHT, 'D');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_DOWN, 'S');

		// ��Ŭ���������� ��ȣ�ۿ�
		GameEngineInput::GetInst()->CreateKey(KEY_INTERACT, VK_LBUTTON);
	}
}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		//HoeDefault* Ptr = GetLevel()->CreateActor<HoeDefault>();
		//Ptr->SetPosition(GetPosition());
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		Direction_ = 24;
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
	{
		Direction_ = 24;
		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		Direction_ = 36;
		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
	{
		Direction_ = 0;
		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}

	GameEngineRenderer* Renderer;
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(Direction_);
	// ��
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(Direction_ + 6);
	// ����
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(Direction_ + 18);
	Renderer = CreateRenderer(IMAGE_PLAYER_HAIR);
	Renderer->SetIndex(Direction_);
}

void Player::Render()
{
	// DebugRectRender();

	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");

	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("�̹��� �ε� ����");
	//}

	//GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
}