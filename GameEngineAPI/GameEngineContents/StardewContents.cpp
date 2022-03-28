#include "StardewContents.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>

StardewContents::StardewContents() 
{
}

StardewContents::~StardewContents() 
{
}

void StardewContents::GameInit()
{
	// 윈도우의 초기 크기 세팅
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	// 플레이어 이미지
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_PLAYER);

	// 폴더안에 모든 이미지 파일을 찾는다.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile(IMAGE_EXT_BMP);

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_CLOTH);
	Image->Cut({ 8, 8 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_HAIR);
	Image->Cut({ 16, 32 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_HAT);
	Image->Cut({ 20, 20 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MASK);
	Image->Cut({ 16, 16 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MAN_BODY);
	Image->Cut({ 16, 32 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_WOMAN_BODY);
	Image->Cut({ 16, 32 });

	// 인터페이스
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_INTERFACE);
		
	AllImageFileList = ResourcesDir.GetAllFile(IMAGE_EXT_BMP);

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	// 툴
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_TOOL);

	AllImageFileList = ResourcesDir.GetAllFile(IMAGE_EXT_BMP);

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	Image = GameEngineImageManager::GetInst()->Find(IMAGE_TOOL_SET1);
	Image->Cut({ 16, 32 });



	// 레벨 생성
	CreateLevel<TitleLevel>(LEVEL_TITLE);
	CreateLevel<PlayLevel>(LEVEL_PLAY);
	CreateLevel<EndingLevel>(LEVEL_ENDING);

	// 시작레벨
	ChangeLevel(LEVEL_TITLE);
}

void StardewContents::GameLoop()
{

}

void StardewContents::GameEnd()
{

}