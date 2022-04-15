#pragma once
#include <string>
#include "ContentsEnums.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>
#include <GameEngineBase/GameEngineTime.h>
#include "Mouse.h"
#include "Item.h"
#include "Clock.h"
#include "EnergyBar.h"
#include "Inventory.h"
#include "PlayerTileIndex.h"

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

	void PlayerInit();

private:
	void Start() override;
	void Update() override;

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

	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision;


	void PlayerAnimationInit();
	void PlayerAnimationChange(const std::string& _Name);
	void PlayerKeyInit();
	void UpdateCamera();

	void CreatePlayerTileIndex(float4 _Pos, std::string _TileMapImageName);

	float4 SetCheckPos(float4 _NextPos);

	void ColWallCheck(float4 _MoveDir);

	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	// Ű �Է�
private:
	Mouse* Mouse_;

	bool IsMoveKeyUp();
	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsActionKeyDown();

	// FSM
public:
	bool ColRenderOrderCheck();
	void StateChange(PlayerState _State);
	void StateUpdate();
private:
	PlayerState CurState_;

	void IdleUpdate();
	void ActionUpdate();
	void MoveUpdate();

	void IdleStart();
	void ActionStart();
	void MoveStart();
	

	// ������ ���õ� ���
private:
	Inventory* Inventory_;
	Clock* Clock_;
	EnergyBar* EnergyBar_;

	// Ÿ�ϸ� ����
private:
	// ������ Ÿ�ϸ��� ����
	GameEngineRendererTileMap* TileMap_;
	// Ÿ�ϸ��� �������ͽ��� ����
	std::vector<std::vector<PlayerTileIndex*>> AllTiles_;
	void SetTile(int x, int y, PlayerTileIndex* _TileMap, int _TileState);
public: 
	// �������� �ڽ��� ũ��� Ÿ���� �����Ͽ� �÷��̾�� Ÿ���� ������ �Ѱ��ֱ� ���� �Լ�
	void SetAllTiles(std::vector<std::vector<PlayerTileIndex*>> _AllTiles)
	{
		AllTiles_ = _AllTiles;
	}

	// �ð� ���� 
private:
	int PlayerTime_;

	void TimeUpdate() {};
};
