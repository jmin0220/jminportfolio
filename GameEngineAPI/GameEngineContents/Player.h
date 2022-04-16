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

	// Ÿ�ϸ� ����
	inline void SetTileMap(GameEngineRendererTileMap* _TileMap)
	{
		TileMap_ = _TileMap;
	}

	// ���� ���� ������ ���
	inline std::string GetNextLevel()
	{
		return NextLevel_;
	}

	// ������������ �÷��̾ ���۵� ��ġ
	inline float4 GetNextLevelPos()
	{
		return NextLevelPos_;
	}

	inline void SetNextLevelPos(float4 _Pos)
	{
		NextLevelPos_ = _Pos;
	}

	// �÷��̾� �ʱ�ȭ
	void PlayerInit();

	// �÷��̾��� ��ġ�� ���� Front���̾��� ���� ������ ���������� ��ȯ
	bool ColRenderOrderCheck();
private:
	void Start() override;
	void Update() override;

	// �ӵ�
	float Speed_; 
	// �÷��̾�� ���������� ���� �ִ� ������ ������ ������ �־�� ��.
	float4 MoveDir_;

	// ���� ����
	std::string NextLevel_;
	// ���� ���������� ��ġ
	static float4 NextLevelPos_;

	// ī�޶��� ��ġ
	float4 CameraPos_;

	// �÷��̾� �ڽ��� ������
	GameEngineRenderer* RendererBody_;

	// �ʿ��� ���� �浹�� �̹���
	GameEngineImage* MapColImage_;

	// �ִϸ��̼� �ʱ�ȭ
	void PlayerAnimationInit();
	// �ִϸ��̼� ��ȯ
	void PlayerAnimationChange(const std::string& _Name);
	// Ű �ʱ�ȭ
	void PlayerKeyInit();
	// ī�޶� ������Ʈ
	void UpdateCamera();

	// �÷��̾ �����϶� �浹����
	float4 SetCheckPos(float4 _NextPos);

	// �ʰ��� �浹üũ
	void ColWallCheck(float4 _MoveDir);

	// ���� ����
	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}

	// Ű �Է�
private:
	bool InventoryClickFlg_;
	int ItemSelectOrigin, ItemSelectTarget;
	Mouse* Mouse_;
	std::vector<GameEngineCollision*> MouseColResult_;

	bool IsMoveKeyDown();
	bool IsMoveKeyPress();
	bool IsMoveKeyUp();
	bool IsActionKeyDown();
	bool IsActionKeyPress();
	bool IsActionKeyUp();

	// ���콺�� �κ��丮�� ����Ʈ �ڽ��� ��Ʈ��
	void ControlInventorySelectBoxWithMouse();

	// FSM
public:
	// ������ȯ
	void StateChange(PlayerState _State);
	// ���� ������Ʈ
	void StateUpdate();
private:
	// ���� ����
	PlayerState CurState_;

	void IdleUpdate();
	void ActionUpdate();
	void MoveUpdate();

	void IdleStart();
	void ActionStart();
	void MoveStart();

private:
	// �������̽�
	Inventory* Inventory_;
	Clock* Clock_;
	EnergyBar* EnergyBar_;

	static int Gold_;

	// Ÿ�ϸ� ����
private:
	// �÷��̾ ���������� Ÿ�� �����ε��� ����
	// Ÿ���� �������� �� ������ Ÿ�ϸ��� ������ ������,
	// �ش� ��ġ�� '����'�� �ش� ������ �÷��̾ ������ ����.
	// ���̴� �Ͱ� ���°� ��ġ���� ���� ���� �ִٴ� �ǹ�.
	void CreatePlayerTileIndex(float4 _Pos, std::string _TileMapImageName);

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

	// TODO::�ð� ���� 
private:
	int PlayerTime_;

	void TimeUpdate() {};
};
