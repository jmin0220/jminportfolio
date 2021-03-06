#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_    = nullptr;
GameEngineLevel* GameEngine::NextLevel_       = nullptr;
GameEngineLevel* GameEngine::PrevLevel_		  = nullptr;
GameEngine*      GameEngine::UserContents_    = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;

HDC GameEngine::BackBufferDC()
{
	return BackBufferImage_->ImageDC();
}

GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}

void GameEngine::GameInit() 
{

}

void GameEngine::GameLoop()
{

}

void GameEngine::GameEnd()
{

}

// 윈도우 창 생성
void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	// 윈도우의 크기를 결정
	UserContents_->GameInit();

	// 윈도우 크기만큼의 버퍼를 생성
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();

	// 1프레임
	UserContents_->GameLoop();

	// 레벨 전환
	if (nullptr != NextLevel_)
	{
		PrevLevel_ = CurrentLevel_;

		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->ActorLevelChangeEnd(NextLevel_);
			CurrentLevel_->LevelChangeEnd(NextLevel_);

			CurrentLevel_->ObjectLevelMoveCheck(NextLevel_);
		}

		GameEngineLevel* PrevLevel = CurrentLevel_;
		CurrentLevel_ = NextLevel_;

		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeStart(PrevLevel);
			CurrentLevel_->ActorLevelChangeStart(PrevLevel);
		}

		NextLevel_ = nullptr;
		GameEngineTime::GetInst()->Reset();

		// 레벨 전환시 화면 클리어
		Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
		Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
	}

		// 에러 판정
	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Current Level is NULL => GameEngine Loop Error");
	}

	// 실행시간 갱신
	GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());
	// 사운드 갱신
	GameEngineSound::Update();

	// 레벨 갱신
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();

	// 액터 렌더링
	CurrentLevel_->ActorRender();

	// 충돌 처리 디버깅
 	CurrentLevel_->CollisionDebugRender();

	// 백버퍼를 메인DC에 복사
	WindowMainImage_->BitCopy(BackBufferImage_);

	CurrentLevel_->ActorRelease();

	// 레벨 리셋
	if (true == CurrentLevel_->IsReset)
	{
		CurrentLevel_->Reset();
		CurrentLevel_->UserResetEnd();
		CurrentLevel_->IsReset = false;
	}
}

// 프로그램 종료
void GameEngine::EngineEnd()
{
	UserContents_->GameEnd();

	std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter  = AllLevel_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == StartIter->second)
		{
			continue;
		}

		delete StartIter->second;
	}


	GameEngineSound::AllResourcesDestroy();
	GameEngineImageManager::Destroy();

	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
	GameEngineWindow::Destroy();
}

// 레벨 전환
void GameEngine::ChangeLevel(const std::string& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

	if (AllLevel_.end() == FindIter)
	{
		MsgBoxAssert("Level Find Error");
		return;
	}

	NextLevel_ = FindIter->second;
}