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
	, ClothPos_({0.0f, 8.0f})
{
}

Player::~Player() 
{
}

void Player::Start()
{
	// Player의 위치와 크기
	SetPosition({1000.0f, 1000.0f});
	

	// 플레이어 캐릭터 렌더링
	// 몸통
	GameEngineRenderer* Renderer;
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_);
	// 팔
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 6);
	// 바지
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 18);
	// 머리카락
	Renderer = CreateRenderer(IMAGE_PLAYER_HAIR);
	Renderer->SetIndex(DirectionHair_);
	// 옷
	Renderer = CreateRenderer(IMAGE_PLAYER_CLOTH);
	Renderer->SetPivot(ClothPos_);
	Renderer->SetIndex(DirectionCloth_);
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

		// 왼클릭했을때의 상호작용
		GameEngineInput::GetInst()->CreateKey(KEY_INTERACT, VK_LBUTTON);
	}

	// 카메라 위치 초기화
	CameraPos_ = GetPosition() - GameEngineWindow::GetInst().GetScale().Half();;
}

void Player::Update()
{
	// 키 입력
	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		HoeBasic* Ptr = GetLevel()->CreateActor<HoeBasic>();
		Ptr->SetPosition(GetPosition());
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
	{
		DirectionBody_ = 24;
		DirectionHair_ = 8;
		DirectionCloth_ = 16;
		DirectionHat_ = 12;
		DirectionMask_ = 8;

		SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		DirectionBody_ = 48;
		DirectionHair_ = 16;
		DirectionCloth_ = 32;
		DirectionHat_ = 24;
		DirectionMask_ = 8;
				
		SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		DirectionBody_ = 72;
		DirectionHair_ = 24;
		DirectionCloth_ = 48;
		DirectionHat_ = 36;

		// 출력 안함
		DirectionMask_ = 48;

		SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
	}
	else if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
	{
		DirectionBody_ = 0;
		DirectionHair_ = 0;
		DirectionCloth_ = 0;
		DirectionHat_ = 0;
		DirectionMask_ = 0;

		SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
	}

	// 이미지
	GameEngineRenderer* Renderer;
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_);
	// 팔
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 6);
	// 바지
	Renderer = CreateRenderer(IMAGE_PLAYER_MAN_BODY);
	Renderer->SetIndex(DirectionBody_ + 18);
	// 머리
	Renderer = CreateRenderer(IMAGE_PLAYER_HAIR);
	Renderer->SetIndex(DirectionHair_);
	// 옷
	Renderer = CreateRenderer(IMAGE_PLAYER_CLOTH);
	Renderer->SetPivot(ClothPos_);
	Renderer->SetIndex(DirectionCloth_);


	// 플레이어의 위치에 맞춰서 카메라 이동
	// 플레이어가 카메라가 움직이는 범위 안에 있을경우 카메라 좌표 갱신
	if ((GetPosition().iy() >= GameEngineWindow::GetInst().GetScale().Half().iy()
		    && GetPosition().iy() <= MAP_FARM_SIZE_H - GameEngineWindow::GetInst().GetScale().Half().iy()))
	{
		CameraPos_.y = GetPosition().iy() - GameEngineWindow::GetInst().GetScale().Half().iy();
	}

	if (GetPosition().iy() <= CameraPos_.y + GameEngineWindow::GetInst().GetScale().Half().iy() - 100.0f)
	{
		CameraPos_.y = GetPosition().iy() - GameEngineWindow::GetInst().GetScale().Half().iy() - 100.0f;
	}
	else if (GetPosition().iy() >= CameraPos_.y + GameEngineWindow::GetInst().GetScale().Half().iy() + 100.0f)
	{
		CameraPos_.y = GetPosition().iy() - GameEngineWindow::GetInst().GetScale().Half().iy() - 100.0f;
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