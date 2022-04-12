#pragma once
#include "ContentsEnums.h"
#include <GameEngine/GameEngineActor.h>
#include <string>
#include <GameEngine/GameEngineRendererTileMap.h>

class FarmTile : public Tile
{
public:
	int TileState_;
};

// ���� :
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

	inline std::string GetNextLevel()
	{
		return NextLevel_;
	}

	inline float4 GetNextLevelPos()
	{
		return NextLevelPos_;
	}

	inline void SetNextLevelPos(float4 _Pos)
	{
		NextLevelPos_ = _Pos;
	}

private:
	float Speed_; 
	// �÷��̾�� ���������� ���� �ִ� ������ ������ ������ �־�� ��.
	float4 MoveDir_;

	std::string NextLevel_;
	static float4 NextLevelPos_;

	// TODO::����
	// float4 ClothPos_;
	float4 CameraPos_;

	GameEngineRenderer* RendererBody_;
	// TODO::����
	//GameEngineRenderer* RendererArms_;
	//GameEngineRenderer* RendererLegs_;
	//GameEngineRenderer* RendererHair_;
	//GameEngineRenderer* RendererCloth_;

	GameEngineRendererTileMap* TileMap_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision;

	void Start() override;
	void Update() override;

	void PlayerAnimationInit();
	void PlayerAnimationChange(const std::string& _Name);
	void PlayerKeyInit();
	void UpdateCamera();

	float4 SetCheckPos(float4 _NextPos);

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
	

	// ������ ���õ� ���
private:
};

