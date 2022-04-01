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
	PlayerAnimationInit();
	PlayerKeyInit();


	// 카메라 위치 초기화
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();;
}

void Player::Update()
{
	// 키 입력
	PlayerControl();

	// 플레이어의 위치에 맞춰서 카메라 이동
	// 플레이어가 카메라가 움직이는 범위 안에 있을경우 카메라 좌표 갱신
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

	// 카메라 위치 갱신
	GetLevel()->SetCameraPos(CameraPos_);
}

void Player::Render()
{
	// DebugRectRender();

	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");

	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("이미지 로딩 실패");
	//}

	//GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
}


void Player::PlayerAnimationInit()
{
	/*
	* https://stardewvalleywiki.com/Modding:Farmer_sprite
	The farmer sprite is drawn in several layers.On the bottom layer is the head, torso, and boots.
	The clothing, accessories, hair, and others are all drawn in multiple layers on top in this order:

	1. Head / Torso / Boots - Bottom layer
	2. Pants
	3. Shirt
	4. Accessories(e.g., glasses, makeup, earrings, facial hair)
	5. Hair
	6. Hat
	7. Arms - Top layer
	*/

	int directionDown = 0;
	int directionRight = 27;
	int directionLeft = 54;
	int directionUp = 81;


	// Player의 위치와 크기
	SetPosition({ 100.0f, 100.0f });

	// 플레이어 캐릭터 렌더링
	RendererBody_ = CreateRenderer();
	RendererLegs_ = CreateRenderer();
	RendererCloth_ = CreateRenderer();
	RendererHair_ = CreateRenderer();
	RendererArms_ = CreateRenderer();

	RendererCloth_->SetPivot(ClothPos_);

	/*
	IMAGE_PLAYER_MAN_BODY파일
	7 / 7 / 6 / 7 = 1줄에 27스프라이트로 구성.
	*/

	// Idle
	// 몸통
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 0 + directionDown, 0 + directionDown, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 0 + directionRight, 0 + directionRight, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 0 + directionLeft, 0 + directionLeft, 0.2f, false);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 0 + directionUp, 0 + directionUp, 0.2f, false);
	// 팔
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 7 + directionDown, 7 + directionDown, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 7 + directionRight, 7 + directionRight, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 7 + directionLeft, 7 + directionLeft, 0.2f, false);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 7 + directionUp, 7 + directionUp, 0.2f, false);
	// 다리
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_DOWN, 20 + directionDown, 20 + directionDown, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_RIGHT, 20 + directionRight, 20 + directionRight, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_LEFT, 20 + directionLeft, 20 + directionLeft, 0.2f, false);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_IDLE_UP, 20 + directionUp, 20 + directionUp, 0.2f, false);

	// Walk
	// 몸
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 0 + directionDown, 3 + directionDown, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 0 + directionRight, 3 + directionRight, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 0 + directionLeft, 3 + directionLeft, 0.2f, true);
	RendererBody_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 0 + directionUp, 3 + directionUp, 0.2f, true);
	// 팔
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 7 + directionDown, 10 + directionDown, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 7 + directionRight, 10 + directionRight, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 7 + directionLeft, 10 + directionLeft, 0.2f, true);
	RendererArms_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 7 + directionUp, 10 + directionUp, 0.2f, true);
	// 다리
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_DOWN, 20 + directionDown, 23 + directionDown, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_RIGHT, 20 + directionRight, 23 + directionRight, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_LEFT, 20 + directionLeft, 23 + directionLeft, 0.2f, true);
	RendererLegs_->CreateAnimation(IMAGE_PLAYER_MAN_BODY, ANIM_WALK_UP, 20 + directionUp, 23 + directionUp, 0.2f, true);

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

	// 초기 애니메이션
	RendererBody_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererLegs_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererCloth_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererHair_->ChangeAnimation(ANIM_IDLE_DOWN);
	RendererArms_->ChangeAnimation(ANIM_IDLE_DOWN);

}

void Player::PlayerKeyInit()
{
	// 키설정
	if (false == GameEngineInput::GetInst()->IsKey(KEY_MOVE_LEFT))
	{
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_LEFT, 'A');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_RIGHT, 'D');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_UP, 'W');
		GameEngineInput::GetInst()->CreateKey(KEY_MOVE_DOWN, 'S');

		// 왼클릭했을때의 상호작용
		GameEngineInput::GetInst()->CreateKey(KEY_INTERACT, VK_LBUTTON);
	}
}

void Player::PlayerControl()
{
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
}