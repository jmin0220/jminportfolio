#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel::PlayLevel()
	: ColMapFlg_(false)
{
	// 캐릭터
	Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	// LEVLE_FARM기준의 시작 포지션
	this->Player_->SetPosition({ 3200.0f, 800.0f });
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
}

void PlayLevel::Update()
{
	Time -= GameEngineTime::GetDeltaTime();

	if (0 >= Time)
	{
		BgmPlayer.Stop();
	}
}


void PlayLevel::TileRangeSetting(int _X, int _Y)
{
	if (0 >= _X)
	{
		MsgBoxAssert("0개인 타일맵을 만들수 없습니다.");
		return;
	}

	if (0 >= _Y)
	{
		MsgBoxAssert("0개인 타일맵을 만들수 없습니다.");
		return;
	}

	GroundTiles_.resize(_Y);
	EnvironmentTiles_.resize(_Y);

	for (size_t y = 0; y < GroundTiles_.size(); y++)
	{
		GroundTiles_[y].resize(_X);

		for (size_t x = 0; x < GroundTiles_[y].size(); x++)
		{
			GroundTiles_[y][x] = nullptr;
		}
	}

	for (size_t y = 0; y < EnvironmentTiles_.size(); y++)
	{
		EnvironmentTiles_[y].resize(_X);

		for (size_t x = 0; x < EnvironmentTiles_[y].size(); x++)
		{
			EnvironmentTiles_[y][x] = nullptr;
		}
	}
}