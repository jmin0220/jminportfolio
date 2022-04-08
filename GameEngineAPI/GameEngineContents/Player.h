#pragma once
#include "ContentsEnums.h"
#include <GameEngine/GameEngineActor.h>
#include <string>

// 설명 :
class GameEngineImage;
class GameEngineCollision;
class GameEngineRendererTileMap;
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		TileMap_ = _TileMap;
	}

private:
	float Speed_; 
	// 플레이어는 마지막으로 보고 있던 방향의 정보를 가지고 있어야 함.
	float4 MoveDir_;

	float4 ClothPos_;
	float4 CameraPos_;

	GameEngineRenderer* RendererBody_;
	GameEngineRenderer* RendererArms_;
	GameEngineRenderer* RendererLegs_;
	GameEngineRenderer* RendererHair_;
	GameEngineRenderer* RendererCloth_;

	GameEngineRendererTileMap* TileMap_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision;

	void Start() override;
	void Update() override;

	void PlayerAnimationInit();
	void PlayerAnimationChange(const std::string& _Name);
	void PlayerKeyInit();
	void UpdateCamera();

	void ColWallCheck(float4 _MoveDir);

	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

private:
	PlayerState CurState_;

	bool IsMoveKeyUp();
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();

	bool IsActionKeyDown();

public:
	bool ColRenderOrderCheck();
	void StateChange(PlayerState _State);
	void StateUpdate();

private:
	void IdleUpdate();
	void ActionUpdate();
	void MoveUpdate();

	void IdleStart();
	void ActionStart();
	void MoveStart();
	
};

