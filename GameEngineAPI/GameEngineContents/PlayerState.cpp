#include "Player.h"
#include "PlayLevel.h"
#include "TileStateTable.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>


void Player::IdleUpdate()
{
	// Idle 상태에서는 액션충돌체 끄기
	GetActionCollision()->Off();

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
	// 애니메이션이 종료되면 액션 실행 후 Idle로 전환
	if (true == RendererBody_->IsEndAnimation())
	{
		float4 CheckLength = MoveDir_ * 24;
		float4 Pos = { GetPosition().x + CheckLength.x, GetPosition().y + CheckLength.y + 12.0f };

		// 액션이 끝나는 순간에만 액션충돌체 켜기
		GetActionCollision()->On();

		if (Inventory_->GetSelectedItem() == ITEM_NAME_HOE)
		{
			// TODO::농작물일경우 부셔짐 처리

			// 타일생성
			CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOW);
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_WATERINGCAN)
		{
			// 타일생성
			CreatePlayerTileIndex(Pos, (int)TILESTATE::HOLLOWWET);
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_AXE)
		{
			// 몰루
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_OAKTREE)
		{
			// 타일생성
			CreatePlayerTileIndex(Pos, (int)TILESTATE::OAKTREE);
		}
		else if (Inventory_->GetSelectedItem() == ITEM_NAME_PARSNIP)
		{
			// 타일생성
			CreatePlayerTileIndex(Pos, (int)TILESTATE::PARSNIP);
		}

		// Idle로 상태 전환
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
		GetActionCollision()->SetPivot({ PLAYER_ACTION_COL_LENG , 0.0f});

		ColCheck(float4::RIGHT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_LEFT))
	{
		PlayerAnimationChange(ANIM_WALK_LEFT);
		GetActionCollision()->SetPivot({ -PLAYER_ACTION_COL_LENG , 0.0f });

		ColCheck(float4::LEFT);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_UP))
	{
		PlayerAnimationChange(ANIM_WALK_UP);
		GetActionCollision()->SetPivot({ 0.0f, -PLAYER_ACTION_COL_LENG });

		ColCheck(float4::UP);
	}
	if (true == GameEngineInput::GetInst()->IsPress(KEY_MOVE_DOWN))
	{
		PlayerAnimationChange(ANIM_WALK_DOWN);
		GetActionCollision()->SetPivot({ 0.0f, PLAYER_ACTION_COL_LENG });

		ColCheck(float4::DOWN);
	}
}


//////////////////////////////////////// State
void Player::IdleStart()
{
	// 정지 상태에서 방향
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_RIGHT);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_LEFT);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_UP);
	}
	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_IDLE_DOWN);
	}
}

void Player::ActionStart()
{
	// TODO::문자열 분리 후 결합하여 애니메이션으로 넘겨줌.
	if (float4::RIGHT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_RIGHT);
	}
	if (float4::LEFT.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_LEFT);
	}
	if (float4::UP.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_UP);
	}
	if (float4::DOWN.CompareInt2D(MoveDir_))
	{
		PlayerAnimationChange(ANIM_HIT_HORIZON_DOWN);
	}
}

void Player::MoveStart()
{

}

