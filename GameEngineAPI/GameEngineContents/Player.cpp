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
	// Player의 위치와 크기
	SetPosition({ 688, 352 });
	CreateRenderer("player.bmp");

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

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		SetMove(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
	{
		SetMove(float4::RIGHT);
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		SetMove(float4::UP);
	}

	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
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
//		MsgBoxAssert("이미지 로딩 실패");
//	}
//
//	GameEngine::BackBufferImage()->BitCopyCenter(FindImage, GetPosition());
//}