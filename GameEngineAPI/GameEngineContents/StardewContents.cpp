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

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(IMAGE_PLAYER_MAN_TOTAL);
	Image->Cut({ 48, 96 });


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

	// Ÿ�ϼ�
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

	// ������ �ڸ��� ������ �κ��丮 ó���� ���� �ڸ��� ó��
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_INVENTORY_EMPTY);
	Image->Cut({ 64, 64 });

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


	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_SEED);
	Image->Cut({ 48, 48 });
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_CROPS);
	Image->Cut({ 64, 128 });
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
	Image = GameEngineImageManager::GetInst()->Find(IMAGE_ENVIRONMENT_FRUIT);
	Image->Cut({ 48, 48 });


	// ��Ʈ
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
	CreateLevel<TownLevel>(LEVEL_TOWN);
	CreateLevel<BeachLevel>(LEVEL_BEACH);
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