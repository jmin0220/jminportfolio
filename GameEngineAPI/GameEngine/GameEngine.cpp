#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_    = nullptr;
GameEngineLevel* GameEngine::NextLevel_       = nullptr;
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
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, WINDOW_GAMEWINDOW);
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	// 윈도우의 크기를 결정
	UserContents_->GameInit();

	// 윈도우 크기만큼의 버퍼를 생성
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create(WINDOW_MAINDC, GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create(WINDOW_BACKBUFFER, GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();

	// 1프레임
	UserContents_->GameLoop();

	// 레벨 전환
	if (nullptr != NextLevel_)
	{
		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeEnd();
		}

		CurrentLevel_ = NextLevel_;

		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeStart();
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
		MsgBoxAssert(DEBUG_MSG_LEVEL_CURRENT_NULL);
	}

	// 실행시간 갱신
	GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

	// 레벨 갱신
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();

	// 충돌 처리
	CurrentLevel_->CollisionDebugRender();

	// 액터 렌더링
	CurrentLevel_->ActorRender();
	
	// 백버퍼를 메인DC에 복사
	WindowMainImage_->BitCopy(BackBufferImage_);

	CurrentLevel_->ActorRelease();
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
		MsgBoxAssert(DEBUG_MSG_LEVEL_FIND_FAILURE);
		return;
	}

	NextLevel_ = FindIter->second;
}