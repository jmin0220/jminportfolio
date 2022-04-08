#include "StardewContents.h"
#include "TitleLevel.h"
#include "FarmLevel.h"
#include "FarmBuildingLevel.h"
#include "TownLevel.h"
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
	// �������� �ʱ� ũ�� ����
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	// �÷��̾� �̹���
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_PLAYER);

	// �����ȿ� ��� �̹��� ������ ã�´�.
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_CLOTH);
	Image->Cut({ 24, 24 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_HAIR);
	Image->Cut({ 48, 96 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_HAT);
	Image->Cut({ 60, 60 }); 
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MASK);
	Image->Cut({ 48, 48 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MAN_BODY);
	Image->Cut({ 48, 96 });
	//Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_WOMAN_BODY);
	//Image->Cut({ 48, 96 });


	// �ǹ�
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_BUILDING);

	// �����ȿ� ��� �̹��� ������ ã�´�.
	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	// ��
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_MAP);

	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	// �������̽�
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_INTERFACE);
		
	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	// ��
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_IMAGE);
	ResourcesDir.Move(DIR_TOOL);

	AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	Image = GameEngineImageManager::GetInst()->Find(IMAGE_TOOL_SET1);
	Image->Cut({ 48, 96 });

	//����
	ResourcesDir.MoveParent(DIR_PARENT);
	ResourcesDir.Move(DIR_RESOURCES);
	ResourcesDir.Move(DIR_SOUND);

	AllImageFileList = ResourcesDir.GetAllFile();

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
	}



	// ���� ����
	CreateLevel<TitleLevel>(LEVEL_TITLE);
	CreateLevel<FarmLevel>(LEVEL_FARM);
	CreateLevel<FarmBuildingLevel>(LEVEL_FARMBUILDING);
	CreateLevel<TownLevel>(LEVEL_TOWN);
	CreateLevel<EndingLevel>(LEVEL_ENDING);

	// ���۷���
	ChangeLevel(LEVEL_TITLE);
}

void StardewContents::GameLoop()
{

}

void StardewContents::GameEnd()
{

}