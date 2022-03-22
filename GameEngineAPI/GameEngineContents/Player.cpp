#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>

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
	SetScale({ 56, 120 });

	CreateRenderer("Idle.bmp");
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