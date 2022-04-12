#include "PlayLevel.h"
#include "GameEngine/GameEngine.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Hoe.h"

PlayLevel::PlayLevel()
{
	// ĳ����
	Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	// LEVLE_FARM������ ���� ������
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
