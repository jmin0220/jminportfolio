#include "Player.h"

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
}

void Player::Render()
{
	DebugRectRender();
}