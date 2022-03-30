#pragma once
#include <GameEngine/GameEngineActor.h>

// ���� :
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
	int DirectionBody_;
	int DirectionHair_;
	int DirectionCloth_;
	int DirectionHat_;
	int DirectionMask_;

	float4 ClothPos_;
	float4 CameraPos_;

	void Start() override;
	void Update() override;
	void Render() override;
};

