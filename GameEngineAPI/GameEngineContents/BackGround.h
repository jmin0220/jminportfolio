#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRendererTileMap.h>

// Ό³Έν :
class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	GameEngineRenderer* GetRenderer()
	{
		return Image_;
	}

	GameEngineRendererTileMap TileMap_;

protected:
	void Start() override;
	void Render() override;

private:
	GameEngineRenderer* Image_;

};

