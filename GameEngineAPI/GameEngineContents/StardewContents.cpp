#include "StardewContents.h"
#include "TitleLevel.h"
#include "FarmLevel.h"
#include "TownLevel.h"
#include "BeachLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>

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
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	// TODO::삭제
	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_CLOTH);
	//Image->Cut({ 24, 24 }); 
	//Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_HAIR);
	//Image->Cut({ 48, 96 }); 
	//Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_HAT);
	//Image->Cut({ 60, 60 }); 
	//Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MASK);
	//Image->Cut({ 48, 48 });
	//Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MAN_BODY);
	//Image->Cut({ 48, 96 });

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MAN_TOTAL);
	Image->Cut({ 48, 96 });


	// 건물
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_BUILDING);

	// 폴더안에 모든 이미지 파일을 찾는다.
	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	// 맵
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_MAP);

	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	// 타일셋
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_TILESET);

	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_TILESET_DIRT);
	Image->Cut({ 48, 48 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_TILESET_DIRTWATERED);
	Image->Cut({ 48, 48 });


	// 인터페이스
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_INTERFACE);
		
	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	// 툴
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_TOOL);

	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	Image = GameEngineImageManager::GetInst()->Find(IMAGE_TOOL_ICON);
	Image->Cut({ 48, 48 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_TOOL_SET1);
	Image->Cut({ 48, 96 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_TOOL_SET2);
	Image->Cut({ 48, 96 });



	// ENVIRONMENT
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_ENVIRONMENT);

	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	// Renderer->RenderPivot::BOT:
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_SEED);
	Image->Cut({ 48, 48 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_CROPS);
	Image->Cut({ 64, 96 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_MAPLETREE);
	Image->Cut({ 144, 624 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_OAKTREE);
	Image->Cut({ 144, 624 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_PINETREE);
	Image->Cut({ 144, 624 });

	// Renderer->RenderPivot::CENTER:
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_FISHING);
	Image->Cut({ 48, 48 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_FORAGE);
	Image->Cut({ 48, 48 });


	// 폰트
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_FONT);

	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	Image = GameEngineImageManager::GetInst()->Find(IMAGE_FONT);
	Image->Cut({ 48, 48 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_FONT_NUMBER);
	Image->Cut({ 24, 48 });


	//사운드
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_SOUND);

	AllImageFileList = ResourcesDir.GetAllFile();

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
	}



	// 레벨 생성
	CreateLevel<TitleLevel>(LEVEL_TITLE);
	CreateLevel<FarmLevel>(LEVEL_FARM);
	CreateLevel<TownLevel>(LEVEL_TOWN);
	CreateLevel<BeachLevel>(LEVEL_BEACH);
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