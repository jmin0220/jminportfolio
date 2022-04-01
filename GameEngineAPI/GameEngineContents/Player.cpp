#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

//#include <GameEngine/GameEngineLevel.h>
#include "PlayLevel.h"
#include "HoeBasic.h"

Player::Player() 
	:Speed_(200.0f)
	, ClothPos_({0.0f, 9.0f})
{
}

Player::~Player() 
{
}

void Player::Start()
{
	int directionDown = 0;
	int directionRight = 24;
	int directionLeft = 48;
	int directionUp = 72;

	// Player�� ��ġ�� ũ��
	SetPosition({0.0f, 0.0f});
	
	

	// �÷��̾� ĳ���� ������
	RendererBody_ = CreateRenderer();
	RendererArms_ = CreateRenderer();
	RendererLegs_ = CreateRenderer();
	RendererHair_ = CreateRenderer();
	RendererCloth_ = CreateRenderer();
	RendererCloth_->SetPivot(ClothPos_);

	// Idle
	// ����
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);
	// ��
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 6 + directionDown, 6 + directionDown, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 6 + directionRight, 6 + directionRight, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 6 + directionLeft, 6 + directionLeft, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 6 + directionUp, 6 + directionUp, 0.2f, false);
	// �ٸ�
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 18 + directionDown, 18 + directionDown, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 18 + directionRight, 18 + directionRight, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 18 + directionLeft, 18 + directionLeft, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 18 + directionUp, 18 + directionUp, 0.2f, false);

	// Walk
	// ��
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 1 + directionDown, 2 + directionDown, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 1 + directionRight, 2 + directionRight, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 1 + directionLeft, 2 + directionLeft, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 1 + directionUp, 2 + directionUp, 0.2f, true);
	// ��
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 6 + directionDown, 7 + directionDown, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 6 + directionRight, 7 + directionRight, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 6 + directionLeft, 7 + directionLeft, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 6 + directionUp, 7 + directionUp, 0.2f, true);
	// �ٸ�
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 19 + directionDown, 20 + directionDown, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 19 + directionRight, 20 + directionRight, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 19 + directionLeft, 20 + directionLeft, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 19 + directionUp, 20 + directionUp, 0.2f, true);

	// Hair
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_RIGHT, 8, 8, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_LEFT, 16, 16, 0.0f, false);
	RendererHair_->CreateAnimation(IMAGE_PLAYER_HAIR, ANIM_IDLE_UP, 24, 24, 0.0f, false);

	// Cloth
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_DOWN, 0, 0, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_RIGHT, 16, 16, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_LEFT, 32, 32, 0.0f, false);
	RendererCloth_->CreateAnimation(IMAGE_PLAYER_CLOTH, ANIM_IDLE_UP, 48, 48, 0.0f, false);

	// �ʱ� �ִϸ��̼�
	RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);


	// Ű����
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOVE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_LEFT, 'A');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_RIGHT, 'D');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_DOWN, 'S');

		// ��Ŭ���������� ��ȣ�ۿ�
		GameEngineInput::GetInst()->CreateKey(KEY_INTERACT, VK_LBUTTON);
	}

	// ī�޶� ��ġ �ʱ�ȭ
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();;
}

void Player::Update()
{
	// Ű �Է�
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		HoeBasic* Ptr = GetLevel()->CreateActor<HoeBasic>();
		Ptr->SetPosition(GetPosition());
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_RIGHT))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererArms_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_RIGHT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_RIGHT);
		}
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_LEFT))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererArms_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_LEFT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_LEFT);
		}
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_UP))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_UP);
			RendererArms_->ChangeAnimation(ANIM_IDLE_UP);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_UP);

			RendererHair_->ChangeAnimation(ANIM_IDLE_UP);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_UP);
		}
		else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_DOWN))
		{
			RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);

			RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);
		}


		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_RIGHT);
			RendererArms_->ChangeAnimation(ANIM_WALK_RIGHT);
			RendererLegs_->ChangeAnimation(ANIM_WALK_RIGHT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_RIGHT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_RIGHT);
			SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
		}
		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_LEFT);
			RendererArms_->ChangeAnimation(ANIM_WALK_LEFT);
			RendererLegs_->ChangeAnimation(ANIM_WALK_LEFT);

			RendererHair_->ChangeAnimation(ANIM_IDLE_LEFT);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_LEFT);
			SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
		}
		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_UP);
			RendererArms_->ChangeAnimation(ANIM_WALK_UP);
			RendererLegs_->ChangeAnimation(ANIM_WALK_UP);

			RendererHair_->ChangeAnimation(ANIM_IDLE_UP);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_UP);
			SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
		}
		if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
		{
			RendererBody_->ChangeAnimation(ANIM_WALK_DOWN);
			RendererArms_->ChangeAnimation(ANIM_WALK_DOWN);
			RendererLegs_->ChangeAnimation(ANIM_WALK_DOWN);

			RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
			RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);
			SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}


	// �÷��̾��� ��ġ�� ���缭 ī�޶� �̵�
	// �÷��̾ ī�޶� �����̴� ���� �ȿ� ������� ī�޶� ��ǥ ����
	if ((GetPosition().iy() >= GameEngineWindow::GetInst().GetScale().Half().iy()
		    && GetPosition().iy() <= MAP_FARM_SIZE_H - GameEngineWindow::GetInst().GetScale().Half().iy()))
	{
		CameraPos_.y = GetPosition().iy() - GameEngineWindow::GetInst().GetScale().Half().iy();
	}

	if ((GetPosition().ix() >= GameEngineWindow::GetInst().GetScale().Half().ix()
		&& GetPosition().ix() <= MAP_FARM_SIZE_W - GameEngineWindow::GetInst().GetScale().Half().ix()))
	{
		CameraPos_.x = GetPosition().ix() - GameEngineWindow::GetInst().GetScale().Half().ix();
	}

	// ī�޶� ��ġ ����
	GetLevel()->SetCameraPos(CameraPos_);
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