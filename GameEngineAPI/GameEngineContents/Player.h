#pragma once
#include <GameEngine/GameEngineActor.h>
#include <string>

// Ό³Έν :
class GameEngineImage;
class GameEngineCollision;
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


protected:

private:
	float Speed_;

	float4 ClothPos_;
	float4 CameraPos_;

	GameEngineRenderer* RendererBody_;
	GameEngineRenderer* RendererArms_;
	GameEngineRenderer* RendererLegs_;
	GameEngineRenderer* RendererHair_;
	GameEngineRenderer* RendererCloth_;

	GameEngineImage* MapColImage_;
	GameEngineCollision* PlayerCollision;

	void Start() override;
	void Update() override;
	void Render() override;

	void PlayerAnimationInit();
	void PlayerKeyInit();
	void PlayerControl();
	void UpdateCamera();

	void ColWallCheck(float4 _MoveDir);

	inline std::string GetCurrentLevel()
	{
		return GetLevel()->GetNameCopy();
	}
};

