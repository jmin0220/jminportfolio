#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h>
#include "HoeBasic.h"

Player::Player() 
	:Speed_(200.0f)
	, DirectionBody_(0)
	, DirectionCloth_(0)
	, DirectionHair_(0)
	, DirectionHat_(0)
	, DirectionMask_(0)
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
	Renderer->SetIndex(DirectionBody_);
	// ��
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 6);
	// ����
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 18);
	// �Ӹ�ī��
	Renderer = CreateRenderer(IMAGE_PLAYER_HAIR);
	Renderer->SetIndex(DirectionHair_);

	//Renderer = CreateRenderer(IMAGE_PLAYER_CLOTH);
	//Renderer->SetIndex(Direction_);
	//Renderer = CreateRenderer(IMAGE_PLAYER_HAT);
	//Renderer->SetIndex(DirectionHat_);
	//Renderer = CreateRenderer(IMAGE_PLAYER_MASK);
	//Renderer->SetIndex(DirectionMask_);

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
		HoeBasic* Ptr = GetLevel()->CreateActor<HoeBasic>();
		Ptr->SetPosition(GetPosition());
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		DirectionBody_ = 24;
		DirectionHair_ = 8;
		DirectionHat_ = 12;
		DirectionMask_ = 8;
		
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
	{
		DirectionBody_ = 24;
		DirectionHair_ = 8;
		DirectionHat_ = 24;
		DirectionMask_ = 8;

		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		DirectionBody_ = 48;
		DirectionHair_ = 16;
		DirectionHat_ = 36;

		// ��� ����
		DirectionMask_ = 48;

		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
	{
		DirectionBody_ = 0;
		DirectionHair_ = 0;
		DirectionHat_ = 0;
		DirectionMask_ = 0;

		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}

	GameEngineRenderer* Renderer;
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_);
	// ��
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 6);
	// ����
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 18);
	// �Ӹ�
	Renderer = CreateRenderer(IMAGE_PLAYER_HAIR);
	Renderer->SetIndex(DirectionHair_);
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