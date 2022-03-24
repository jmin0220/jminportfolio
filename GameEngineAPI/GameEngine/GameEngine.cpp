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

// ������ â ����
void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, WINDOW_GAMEWINDOW);
	GameEngineWindow::GetInst().ShowGameWindow();
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	// �������� ũ�⸦ ����
	UserContents_->GameInit();

	// ������ ũ�⸸ŭ�� ���۸� ����
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create(WINDOW_MAINDC, GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create(WINDOW_BACKBUFFER, GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();

	// 1������
	UserContents_->GameLoop();

	// ���� ��ȯ
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
	}

		// ���� ����
	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert(DEBUG_MSG_LEVEL_CURRENT_NULL);
	}

	// ����ð� ����
	GameEngineInput::GetInst()->Update();

	// ���� ����
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();

	// ���� ������
	CurrentLevel_->ActorRender();
	
	// ����۸� ����DC�� ����
	WindowMainImage_->BitCopy(BackBufferImage_);
}

// ���α׷� ����
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

	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
}

// ���� ��ȯ
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