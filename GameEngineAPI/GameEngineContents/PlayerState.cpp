#include "Player.h"
#include "PlayLevel.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


void Player::IdleUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}

	if (true == IsMoveKeyDown())
	{
		StateChange(PlayerState::Move);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown(KEY_INTERACT))
	{
		StateChange(PlayerState::Action);
		return;
	}
}

// 클릭했을때 상태
void Player::ActionUpdate()
{
	// 애니메이션이 종료되면 Idle로 전환
	if (true == RendererBody_->IsEndAnimation())
	{
		TileMap_->CreateTile(GetPosition(), IMAGE_FARM_BUILDING);
		StateChange(PlayerState::Idle);
	}
}

// 이동했을때 상태
void Player::MoveUpdate()
{
	// 액션은 이동보다 우선순위가 높음.
	if (true == IsActionKeyDown())
	{
		StateChange(PlayerState::Action);
		return;
	}
	if (true == IsMoveKeyUp() && false == IsMoveKeyPress())
	{
		StateChange(PlayerState::Idle);
		return;
	}

	// 이동 상태에서 방향
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_RIGHT))
	{
		PlayerAnimationChange(ANIM_WALK_RIGHT);

		ColWallCheck(float4::RIGHT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		PlayerAnimationChange(ANIM_WALK_LEFT);

		ColWallCheck(float4::LEFT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		PlayerAnimationChange(ANIM_WALK_UP);

		ColWallCheck(float4::UP);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
	{
		PlayerAnimationChange(ANIM_WALK_DOWN);

		ColWallCheck(float4::DOWN);
	}
}


//////////////////////////////////////// State

void Player::IdleStart()
{
	// 정지 상태에서 방향
	if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_RIGHT))
	{
		PlayerAnimationChange(ANIM_IDLE_RIGHT);

		ColWallCheck(float4::ZERO);
	}
	else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_LEFT))
	{
		PlayerAnimationChange(ANIM_IDLE_LEFT);

		ColWallCheck(float4::ZERO);
	}
	else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_UP))
	{
		PlayerAnimationChange(ANIM_IDLE_UP);

		ColWallCheck(float4::ZERO);
	}
	else if (true == GameEngineInput::GetInst()->IsUp(KEY_MOVE_DOWN))
	{
		PlayerAnimationChange(ANIM_IDLE_DOWN);

		ColWallCheck(float4::ZERO);
	}
}

void Player::ActionStart()
{

}

void Player::MoveStart()
{

}

