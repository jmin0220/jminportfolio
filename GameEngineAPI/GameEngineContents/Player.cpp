#include "Player.h"

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
	SetScale({ 56, 120 });
}

void Player::Render()
{
	DebugRectRender();
}